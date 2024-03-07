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
class IResponseInterface : public IResponseWare, IRegisterMetaTypeUnit<T>
{
public:
    using IResponseWare::operator[];

public:
    IResponseInterface() = default;
    virtual ~IResponseInterface() = default;

    // TODO: 这里需要将 注册方式抽象， 继承 Task 功能
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
typename IResponseInterface<T>::IResponseInterfacePrivate
         IResponseInterface<T>::m_IResponseInterfacePrivate;

$PackageWebCoreEnd
