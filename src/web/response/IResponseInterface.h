#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "web/biscuits/IHttpStatus.h"
#include "web/biscuits/IHttpMime.h"
#include "web/response/IResponseManage.h"
#include "web/response/IResponseWare.h"
#include "core/unit/IRegisterMetaTypeUnit.h"

$PackageWebCoreBegin

struct IResponseWareRaw;
class IRedirectResponse;

template<typename T>
class IRegisterResponseType
{

private:
    class IRegisterResponseTypePrivate{
    public:
        IRegisterResponseTypePrivate(){
            static std::once_flag flag;
            std::call_once(flag, [](){
                static T t;
                IResponseManage::registerResponseType(&t);
            });
        }
    };
    friend class IRegisterResponseTypePrivate;
    static IRegisterResponseTypePrivate m_IRegisterResponseTypePrivate;
    virtual void* IRegisterResponseTypePrivateTouch(){
        return &m_IRegisterResponseTypePrivate;
    }
}

template<typename T>
typename IResponseInterface<T>::IRegisterResponseTypePrivate
         IResponseInterface<T>::m_IRegisterResponseTypePrivate;


template<typename T>
class IResponseInterface : public IResponseWare, IRegisterMetaTypeUnit<T>, IRegisterResponseType<T>
{
public:
    using IResponseWare::operator[];

public:
    IResponseInterface() = default;
    virtual ~IResponseInterface() = default;
};


$PackageWebCoreEnd
