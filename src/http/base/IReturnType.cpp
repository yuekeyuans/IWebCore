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
#include "http/response/IStatusResponse.h"
#include "http/response/IRedirectResponse.h"
#include "http/net/impl/IRequestImpl.h"

$PackageWebCoreBegin

class IReturnTypeDetail : public IReturnType
{
public:
    IReturnTypeDetail(QMetaType::Type type, const QString& name);

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

IReturnTypeDetail::IReturnTypeDetail(QMetaType::Type type, const QString& name)
{
    typeId = type;
    typeName = name;
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
    if(IResponseManage::instance()->containResponseType(typeName)){
        m_resolveFunction = [](IRequestImpl& impl, void* ptr){
            impl.setResponseWare(*static_cast<IResponseWare*>(ptr));
        };
    }
}

void IReturnTypeDetail::createBeanFun()
{
    if(IBeanTypeManage::instance()->isBeanIdExist(typeId)){
        m_resolveFunction = [](IRequestImpl& impl, void* ptr){
            IJson json = static_cast<IBeanWare*>(ptr)->toJson();
            impl.setResponseWare(IJsonResponse(std::move(json)));
        };
    }
}

void IReturnTypeDetail::createVoidFun()
{
    if(typeId == QMetaType::Void){
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
    if(typeId == QMetaType::UnknownType && typeName == "IHttpStatus" || typeId == QMetaType::Int){
        m_resolveFunction = [](IRequestImpl& impl, void* ptr){
            impl.setResponseWare(IStatusResponse(*static_cast<int*>(ptr))); // TODO: 查看转换问题
        };
    }
}

void IReturnTypeDetail::createStdStringFun()
{
    if(typeId == (QMetaType::Type)qMetaTypeId<std::string>()){
        m_resolveFunction = [](IRequestImpl& impl, void* ptr){
            QString value = QString::fromStdString(*static_cast<std::string*>(ptr));
            if(value.startsWith("$")){
                IResponseWare* ware = IResponseManage::instance()->convertMatch(value);
                if(ware){
                    auto content = ware->prefixCreate(std::move(value));
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
    if(typeId == QMetaType::QString){
        m_resolveFunction = [](IRequestImpl& impl, void* ptr){
            QString& value = *static_cast<QString*>(ptr);
            if(value.startsWith("$")){
                IResponseWare* ware = IResponseManage::instance()->convertMatch(value);
                if(ware){
                    auto content = ware->prefixCreate(std::move(value));
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
    if(typeId == QMetaType::QByteArray){
        m_resolveFunction = [](IRequestImpl& impl, void *ptr){
            QByteArray& array = *static_cast<QByteArray*>(ptr);
            impl.setResponseWare(IByteArrayResponse(std::move(array)));
        };
    }
}

void IReturnTypeDetail::createIJsonFun()
{
    if(typeId == (QMetaType::Type)qMetaTypeId<IJson>()){
        m_resolveFunction = [](IRequestImpl& impl, void* ptr){
            impl.setResponseWare(IJsonResponse(*static_cast<IJson*>(ptr)));
        };
    }
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

void IReturnType::resolveValue(IRequestImpl& impl, void *ptr) const
{
    m_resolveFunction(impl, ptr);
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
