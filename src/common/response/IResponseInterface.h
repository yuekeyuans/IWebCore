#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "biscuits/IHttpStatus.h"
#include "biscuits/IHttpMime.h"
#include "common/support/IRegisterMetaTypeUnit.h"

#include "common/response/IResponseManage.h"
#include "common/response/IResponseWare.h"

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
