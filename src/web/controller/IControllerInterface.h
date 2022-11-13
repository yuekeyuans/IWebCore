#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/task/IControllerTaskUnit.h"
#include "web/controller/IControllerManage.h"
#include "web/controller/private/IControllerInfo.h"

$PackageWebCoreBegin

struct IControllerInfo;

namespace IControllerInterfaceProxy
{
    void registerController(const IControllerInfo& info);
    void registerError();

    void unRegisterController(const IControllerInfo& info);
    void unRegisterError();
};

template<typename T, bool enabled = true>
class IControllerInterface : public IControllerTaskUnit<T, enabled>
{
public:
    IControllerInterface() = default;
    virtual ~IControllerInterface() = default;

    virtual void task() final;
    virtual void registerController() final;
    virtual void unRegisterController() final;
};

template<typename T, bool enabled>
void IControllerInterface<T, enabled>::task()
{
    registerController();
}

template<typename T, bool enabled>
void IControllerInterface<T, enabled>::registerController()
{
    if(this != T::instance()){
        IControllerInterfaceProxy::registerError();
    }

    IControllerInfo info;
    info.handler = this;
    info.className = IMetaUtil::getMetaClassName (T::staticMetaObject);
    info.clsInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    info.methods = IMetaUtil::getMetaMethods(T::staticMetaObject);
    IControllerInterfaceProxy::registerController(info);
}

template<typename T, bool enabled>
void IControllerInterface<T, enabled>::unRegisterController()
{
    if(this !=  T::instance()){
        IControllerInterfaceProxy::unRegisterError();
    }

    IControllerInfo info;
    info.handler = this;
    info.className = IMetaUtil::getMetaClassName (T::staticMetaObject);
    info.clsInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    info.methods = IMetaUtil::getMetaMethods(T::staticMetaObject);
    IControllerInterfaceProxy::unRegisterController(info);
}

$PackageWebCoreEnd
