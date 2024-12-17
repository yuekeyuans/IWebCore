#include "IReturnType.h"
#include "core/util/ISpawnUtil.h"
#include "core/util/IStringUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/bean/IBeanWare.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/response/IJsonResponse.h"
#include "http/response/IByteArrayResponse.h"
#include "http/response/IPlainTextResponse.h"
#include "http/response/IFileResponse.h"
#include "http/response/IResponseWare.h"
#include "http/response/IStatusResponse.h"
#include "http/response/IRedirectResponse.h"
#include "http/net/impl/IRequestImpl.h"

$PackageWebCoreBegin

class IReturnTypeDetail : public IReturnType
{
public:
    IReturnTypeDetail(QMetaType::Type type, const std::string& name);

private:
    void createResolveFuntion();

private:
    void createResponseFun();
    void createBeanFun();
    void createVoidFun();
    void createStatusFun();
    void createStdStringFun();
    void createQStringFun();
    void createQByteArrayFun();
    void createIJsonFun();
};

IReturnTypeDetail::IReturnTypeDetail(QMetaType::Type type, const std::string& name)
{
    m_typeId = type;
    m_typeName = name;
    createResolveFuntion();
}

void IReturnTypeDetail::createResolveFuntion()
{
    QVector<decltype(&IReturnTypeDetail::createResponseFun)> funs = {
            &IReturnTypeDetail::createResponseFun,
            &IReturnTypeDetail::createBeanFun,
            &IReturnTypeDetail::createVoidFun,
            &IReturnTypeDetail::createStatusFun,
            &IReturnTypeDetail::createStdStringFun,
            &IReturnTypeDetail::createQStringFun,
            &IReturnTypeDetail::createQByteArrayFun,
            &IReturnTypeDetail::createIJsonFun,
    };
    for(auto fun : funs){
        std::bind(fun, this)();
    }
    if(!m_resolveFunction){
        qFatal("return type can not be resolved");
    }
}

void IReturnTypeDetail::createResponseFun()
{
    if(IResponseManage::instance()->containResponse(m_typeName)){
        m_resolveFunction = [](IRequestImpl& impl, void* ptr){
            impl.setResponseWare(*static_cast<IResponseWare*>(ptr));
        };
    }
}

void IReturnTypeDetail::createBeanFun()
{
    if(IBeanTypeManage::instance()->isBeanIdExist(m_typeId)){
        m_resolveFunction = [](IRequestImpl& impl, void* ptr){
            IJson json = static_cast<IBeanWare*>(ptr)->toJson();
            impl.setResponseWare(IJsonResponse(std::move(json)));
        };
    }
}

void IReturnTypeDetail::createVoidFun()
{
    if(m_typeId == QMetaType::Void){
        m_resolveFunction = [](IRequestImpl& impl, void*){
            if(impl.m_respRaw.m_mime == IHttpMimeUtil::MIME_UNKNOWN_STRING){
                impl.m_respRaw.setMime(IHttpMime::TEXT_PLAIN_UTF8);
            }
            if(impl.m_respRaw.m_status == IHttpStatus::UNKNOWN){
                impl.m_respRaw.m_status = IHttpStatus::OK_200;
            }
        };
    }
}

void IReturnTypeDetail::createStatusFun()
{
    if(m_typeId == QMetaType::UnknownType && m_typeName == "IHttpStatus" || m_typeId == QMetaType::Int){
        m_resolveFunction = [](IRequestImpl& impl, void* ptr){
            impl.setResponseWare(IStatusResponse(*static_cast<int*>(ptr)));
        };
    }
}

void IReturnTypeDetail::createStdStringFun()
{
    if(m_typeId == QMetaType::UnknownType && m_typeName == "std::string"){
        m_resolveFunction = [](IRequestImpl& impl, void* ptr){
            const std::string& value = *static_cast<std::string*>(ptr);
            if(IStringUtil::startsWith(value, "$")){
                IResponseWare* ware = IResponseManage::instance()->convertableMatch(value);
                if(ware){
                    auto content = ware->prefixCreate(value);
                    impl.setResponseWare(*content);
                    delete content;
                    return;
                }
            }

            impl.setResponseWare(IPlainTextResponse(std::move(value)));
        };
    }
}

void IReturnTypeDetail::createQStringFun()
{
    if(m_typeId == QMetaType::QString){
        m_resolveFunction = [](IRequestImpl& impl, void* ptr){
            std::string value = static_cast<QString*>(ptr)->toStdString();
            if(IStringUtil::startsWith(value, "$")){
                IResponseWare* ware = IResponseManage::instance()->convertableMatch(value);
                if(ware){
                    auto content = ware->prefixCreate(value);
                    impl.setResponseWare(*content);
                    delete content;
                    return;
                }
            }
            impl.setResponseWare(IPlainTextResponse(std::move(value)));
        };
    }
}

void IReturnTypeDetail::createQByteArrayFun()
{
    if(m_typeId == QMetaType::QByteArray){
        m_resolveFunction = [](IRequestImpl& impl, void *ptr){
            QByteArray& array = *static_cast<QByteArray*>(ptr);
            impl.setResponseWare(IByteArrayResponse(std::move(array)));
        };
    }
}

void IReturnTypeDetail::createIJsonFun()
{
    if(m_typeId == QMetaType::UnknownType && m_typeName == "IJson"){
        m_resolveFunction = [](IRequestImpl& impl, void* ptr){
            impl.setResponseWare(IJsonResponse(*static_cast<IJson*>(ptr)));
        };
    }
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
