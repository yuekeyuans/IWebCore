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
    void createResolveFuntion();
};

IReturnTypeDetail::IReturnTypeDetail(QMetaType::Type type, const QString& name)
{
    typeId = type;
    typeName = name;
    chechMethodSupportedReturnType();
    createResolveFuntion();
}

void IReturnTypeDetail::chechMethodSupportedReturnType()
{
    auto val = false
            || typeId == QMetaType::UnknownType && typeName == "IHttpStatus"
            || typeId == QMetaType::Int
            || typeId == QMetaType::Void
            || typeId == QMetaType::QString
            || typeId == (QMetaType::Type)qMetaTypeId<std::string>()
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

void IReturnTypeDetail::createResolveFuntion()
{
    if(typeId == QMetaType::UnknownType && typeName == "IHttpStatus" || typeId == QMetaType::Int){
        m_resolveFunction = [](IRequest&, IResponse& response, void* ptr){
            response.setContent((IResponseWare&)IStatusResponse(*static_cast<int*>(ptr))); // TODO: 查看转换问题
        };
    }

    if(typeId == QMetaType::Void){
        m_resolveFunction = [](IRequest&, IResponse&response, void*){
            if(response.mime() == IHttpMimeUtil::MIME_UNKNOWN_STRING){
                response.setMime(IHttpMime::TEXT_PLAIN_UTF8);
            }
            if(response.status() == IHttpStatus::UNKNOWN){
                response.setStatus(IHttpStatus::OK_200);
            }
        };
    }

    if(typeId == QMetaType::QString){
        m_resolveFunction = [](IRequest&, IResponse&response, void* ptr){
            QString& value = *static_cast<QString*>(ptr);
            if(value.startsWith("$")){
                IResponseWare* ware = IResponseManage::instance()->convertMatch(value);
                if(ware){
                    // TODO: 这个更改掉
//                    return response.setContent(ware->create(std::move(value)));
                }
            }
            response.setContent((IResponseWare&)IPlainTextResponse(std::move(value)));
        };
    }

    if(typeId == (QMetaType::Type)qMetaTypeId<std::string>()){
        m_resolveFunction = [](IRequest&, IResponse&response, void* ptr){
            QString value = QString::fromStdString(*static_cast<std::string*>(ptr));
            if(value.startsWith("$")){
                IResponseWare* ware = IResponseManage::instance()->convertMatch(value);
                if(ware){
                    // TODO: 这个更改掉
//                    return response.setContent(ware->create(std::move(value)));
                }
            }
            response.setContent((IResponseWare&)IPlainTextResponse(std::move(value)));
        };
    }

    if(typeId == (QMetaType::Type)qMetaTypeId<IJson>()){
        m_resolveFunction = [](IRequest&, IResponse&response, void* ptr){
            response.setContent((IResponseWare&)IJsonResponse((*static_cast<IJson*>(ptr)).dump()));
        };
    }

    if(IBeanTypeManage::instance()->isBeanIdExist(typeId)){
        m_resolveFunction = [](IRequest&, IResponse&response, void* ptr){
            IJson json = static_cast<IBeanWare*>(ptr)->toJson();
            response.setContent((IResponseWare&)IJsonResponse(json));
        };
    }

}

namespace detail
{
    void wrapVoidReturnInstance(IResponse &response);
    QSharedPointer<IResponseWare> createQStringReturnInstance(void *ptr);   // TODO: 检查这个是否有性能浪费
    QSharedPointer<IResponseWare> createStdStringReturnInstance(void*ptr);
}

void *IReturnType::create() const
{
    if(typeId == QMetaType::UnknownType && typeName == "IHttpStatus"){
        return QMetaType::create(QMetaType::Int);
    }
    return QMetaType::create(typeId);
}

void IReturnType::destroy(void *ptr) const
{
    if(typeId == QMetaType::UnknownType && typeName == "IHttpStatus"){
        return QMetaType::destroy(QMetaType::Int, ptr);
    }
    return QMetaType::destroy(typeId, ptr);
}

void IReturnType::resolveValue(IRequest &request, void *ptr) const
{
    IResponse response(request);
    m_resolveFunction(request, response, ptr);
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
