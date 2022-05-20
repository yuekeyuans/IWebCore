#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "web/biscuits/IHttpStatus.h"
#include "web/biscuits/IHttpMime.h"
#include "web/response/IResponseManage.h"
#include "web/response/IResponseWare.h"
#include "core/unit/IRegisterMetaTypeUnit.h"

$PackageWebCoreBegin

struct IResponseWareRaw;
class IRedirectResponse;

template<typename T>
class IResponseInterface : public IResponseWare, public IRegisterMetaTypeUnit<T>
{
    $UseWare
public:
    using IResponseWare::operator[];

public:
    IResponseInterface() = default;
    virtual ~IResponseInterface() = default;

private:
    class IResponseInterfacePrivate{
    public:
        IResponseInterfacePrivate(){
            static T t;
            IResponseManage::registerResponseType(&t);
        }
    };
    friend class IResponseInterfacePrivate;
    static IResponseInterfacePrivate m_IResponseInterfacePrivate;
    virtual void* IResponseInterfacePrivateTouch(){
        return &m_IResponseInterfacePrivate;
    }
};

template<typename T>
typename IResponseInterface<T>::IResponseInterfacePrivate  IResponseInterface<T>::m_IResponseInterfacePrivate;

$PackageWebCoreEnd
