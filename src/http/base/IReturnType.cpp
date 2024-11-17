#include "IReturnType.h"
#include "core/util/ISpawnUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/response/IStatusResponse.h"
#include "http/response/IJsonResponse.h"
#include "http/response/IByteArrayResponse.h"
#include "http/response/IFileResponse.h"
#include "http/response/IResponseWare.h"
#include "http/response/IPlainTextResponse.h"

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
    if(typeId == QMetaType::UnknownType){
//        auto reason = QString("return Type Not Defined in QMeta System. type: ").append(typeName);
        qFatal("error");
//        IMethodNodeAbort::abortcontroller_invalid_parameter_type(reason, $ISourceLocation);
    }

    const static QString info = "this kind of return type not supported, please change the return type!";

    const static  QVector<QMetaType::Type> validMetaType = {
        QMetaType::Void,
        QMetaType::Int,
        QMetaType::QString,
//        QMetaType::QJsonArray,
//        QMetaType::QJsonObject,
//        QMetaType::QJsonValue,
//        QMetaType::QByteArray,
        //        QMetaType::QStringList,
    };

    if(validMetaType.contains(typeId)){
        return;
    }

    if(IBeanTypeManage::instance()->isBeanIdExist(typeId)){
        return;
    }

    // TODO: 这个不能这样判断，应为用户可能不按照这个名字写转换
    if(typeName.startsWith("I") && typeName.endsWith("Response")){
        return;
    }

    if(typeId == QMetaType::UnknownType){
//        auto errorInfo = info + "the error take place in Function : " + node.methodNode.signature;
        qFatal("error");
    }

//    auto errorInfo = info + "the error take place in Function : " + node.methodNode.signature;
    qFatal("error");
}

namespace ISpawnUtil
{
    template<>
    IReturnType construct(int type, const char* name)
    {
        return IReturnTypeDetail(QMetaType::Type(type), name);
    }
}

void *IReturnType::create() const
{
    return QMetaType::create(typeId);
}

void IReturnType::destroy(void *ptr) const
{
    QMetaType::destroy(typeId, ptr);
}


// TODO: 这里检查一下
void wrapVoidReturnInstance(IResponse &response)
{
    if(response.mime() == IHttpMimeUtil::MIME_UNKNOWN_STRING){
        response.setMime(IHttpMime::TEXT_PLAIN_UTF8);
    }
    if(response.status() == IHttpStatusCode::UNKNOWN){
        response.setStatus(IHttpStatusCode::OK_200);
    }
}

QSharedPointer<IResponseWare> createStringReturnInstance(void *ptr)
{
    auto value = *static_cast<QString*>(ptr);
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
    IResponse response(&request);
    QSharedPointer<IResponseWare> responseWare;
    switch (typeId) {
    case QMetaType::Void:
        wrapVoidReturnInstance(response);
        return;
    case QMetaType::QString:
        responseWare = createStringReturnInstance(ptr);
        break;
    case QMetaType::Int:
        responseWare = QSharedPointer<IStatusResponse>::create(*static_cast<int*>(ptr));;
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
//    case QMetaType::QStringList:
//        responseWare = QSharedPointer<IPlainTextResponse>::create(IConvertUtil::toString(*static_cast<QStringList*>(ptr)));
//        break;
    default:
        if(typeName.startsWith("I") && typeName.endsWith("Response")){
            response.setContent(static_cast<IResponseWare*>(ptr));
            return;
        }else{
            QString info = typeName + " not supported, please change the return type!";
            qFatal(info.toUtf8());
        }
    }
    response.setContent(responseWare.data());

}

$PackageWebCoreEnd
