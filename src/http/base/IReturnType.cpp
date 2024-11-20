#include "IReturnType.h"
#include "core/util/ISpawnUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/bean/IBeanWare.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/response/IJsonResponse.h"
#include "http/response/IByteArrayResponse.h"
#include "http/response/IFileResponse.h"
#include "http/response/IResponseWare.h"
#include "http/response/IPlainTextResponse.h"
#include "http/response/IInvalidResponse.h"
#include "http/response/IStatusResponse.h"
#include "http/response/IRedirectResponse.h"

$PackageWebCoreBegin

class IReturnTypeDetail : public IReturnType
{
public:
    IReturnTypeDetail(QMetaType::Type type, const QString& name);

private:
    void chechMethodSupportedReturnType();
};

IReturnTypeDetail::IReturnTypeDetail(QMetaType::Type type, const QString& name)
{
    typeId = type;
    typeName = name;
    chechMethodSupportedReturnType();
}

void IReturnTypeDetail::chechMethodSupportedReturnType()
{
    auto val = false
            || typeId == QMetaType::UnknownType && typeName == "IHttpStatus"
            || typeId == QMetaType::Int
            || typeId == QMetaType::Void
            || typeId == QMetaType::QString || typeId == (QMetaType::Type)qMetaTypeId<std::string>()
            || typeId == QMetaType::QJsonArray
            || typeId == QMetaType::QJsonObject
            || typeId == QMetaType::QJsonValue
            || typeId == (QMetaType::Type)qMetaTypeId<IJson>()
            || IBeanTypeManage::instance()->isBeanIdExist(typeId)
            || IResponseManage::instance()->containResponseType(typeName);

    if(!val){
        qFatal("error return type");
    }
}

void *IReturnType::create() const
{
    if(typeId == QMetaType::UnknownType){
        return QMetaType::create(QMetaType::Int);
    }
    return QMetaType::create(typeId);
}

void IReturnType::destroy(void *ptr) const
{
    if(typeId == QMetaType::UnknownType){
        return QMetaType::destroy(QMetaType::Int, ptr);
    }
    return QMetaType::destroy(typeId, ptr);
}

void wrapVoidReturnInstance(IResponse &response)
{
    if(response.mime() == IHttpMimeUtil::MIME_UNKNOWN_STRING){
        response.setMime(IHttpMime::TEXT_PLAIN_UTF8);
    }
    if(response.status() == IHttpStatus::UNKNOWN){
        response.setStatus(IHttpStatus::OK_200);
    }
}

// TODO: 检查这个是否有性能浪费
QSharedPointer<IResponseWare> createQStringReturnInstance(void *ptr)
{
    QString value = *static_cast<QString*>(ptr);
    if(value.startsWith("$")){
        IResponseWare* response = IResponseManage::instance()->convertMatch(value);
        if(response){
            return response->create(std::move(value)); // TODO: 这里应该使用函数优化掉这个内容
        }
    }
    return QSharedPointer<IPlainTextResponse>::create(std::move(value));
}

QSharedPointer<IResponseWare> createStdStringReturnInstance(void*ptr)
{
    QString value = QString::fromStdString(*static_cast<std::string*>(ptr));
    if(value.startsWith("$")){
        IResponseWare* response = IResponseManage::instance()->convertMatch(value);
        if(response){
            return response->create(std::move(value)); // TODO: 这里应该使用函数优化掉这个内容
        }
    }
    return QSharedPointer<IPlainTextResponse>::create(std::move(value));
}

void IReturnType::resolveValue(IRequest &request, void *ptr) const
{
    IResponse response(request);
    if(IResponseManage::instance()->containResponseType(typeName)){
        response.setContent(static_cast<IResponseWare*>(ptr));
        return;
    }

    QSharedPointer<IResponseWare> responseWare{};
    switch (typeId) {
    case QMetaType::Void:
        wrapVoidReturnInstance(response);
        return;
    case QMetaType::UnknownType:    // only IHttpStatus are unknown type.
    case QMetaType::Int:
        responseWare = QSharedPointer<IStatusResponse>::create(*static_cast<int*>(ptr));
        break;
    case QMetaType::QString:
        responseWare = createQStringReturnInstance(ptr);
        break;
    case QMetaType::QJsonArray:
        responseWare = QSharedPointer<IJsonResponse>::create(*static_cast<QJsonArray*>(ptr));
        break;
    case QMetaType::QJsonObject:
        responseWare = QSharedPointer<IJsonResponse>::create(*static_cast<QJsonObject*>(ptr));
        break;
    case QMetaType::QJsonValue:
        responseWare = QSharedPointer<IJsonResponse>::create(*static_cast<QJsonObject*>(ptr));
        break;
    case QMetaType::QByteArray:
        responseWare = QSharedPointer<IByteArrayResponse>::create(*static_cast<QByteArray*>(ptr));
        break;
    }

    if(!responseWare){
        if(IBeanTypeManage::instance()->isBeanIdExist(typeId)){
            IJson json = static_cast<IBeanWare*>(ptr)->toJson();
            responseWare = QSharedPointer<IJsonResponse>::create(json.dump());
        }
        if(typeId == static_cast<QMetaType::Type>(qMetaTypeId<std::string>())){
            responseWare = createStdStringReturnInstance(ptr);
        }
        if(typeId == static_cast<QMetaType::Type>(qMetaTypeId<IJson>())){
            IJson json = *static_cast<IJson*>(ptr);
            responseWare = QSharedPointer<IJsonResponse>::create(json.dump());
        }
    }

    if(!responseWare){
        qFatal("error");
    }

    response.setContent(responseWare.data());
}

namespace ISpawnUtil
{
    template<>
    IReturnType construct(int type, const char* name)
    {
        return IReturnTypeDetail(QMetaType::Type(type), name);
    }
}

$PackageWebCoreEnd
