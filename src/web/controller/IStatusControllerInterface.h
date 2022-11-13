#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/configuration/IConfigurationManage.h"
#include "core/task/IControllerTaskUnit.h"
#include "web/controller/IControllerManage.h"
#include "web/controller/private/IControllerInfo.h"
#include "web/node/IStatusActionNode.h"

$PackageWebCoreBegin

struct IControllerInfo;

namespace IStatusControllerInterfaceProxy
{
    void registerController(const IControllerInfo& info);
    void registerError();

    void unRegisterController(const IControllerInfo& info);
    void unRegisterError();
}

template<typename T, bool enabled = true>
class IStatusControllerInterface : public IControllerTaskUnit<T, enabled>
{
public:
    IStatusControllerInterface() = default;
    virtual ~IStatusControllerInterface() = default;

    virtual void task() final;
    virtual void registerController() final;
    virtual void unRegisterController() final;
};

template<typename T, bool enabled>
void IStatusControllerInterface<T, enabled>::task()
{
    registerController();
}

template<typename T, bool enabled>
void IStatusControllerInterface<T, enabled>::registerController()
{
    if(this != T::instance()){
        IStatusControllerInterfaceProxy::registerError();
    }

    IControllerInfo info;
    info.handler = this;
    info.className = IMetaUtil::getMetaClassName (T::staticMetaObject);
    info.clsInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    info.methods = IMetaUtil::getMetaMethods(T::staticMetaObject);
    IStatusControllerInterfaceProxy::registerController(info);
}

template<typename T, bool enabled>
void IStatusControllerInterface<T, enabled>::unRegisterController()
{
    if(this != T::instance()){
        IStatusControllerInterfaceProxy::unRegisterError();
    }

    IControllerInfo info;
    info.handler = this;
    info.className = IMetaUtil::getMetaClassName (T::staticMetaObject);
    info.clsInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    info.methods = IMetaUtil::getMetaMethods(T::staticMetaObject);
    IStatusControllerInterfaceProxy::unRegisterController(info);
}

$PackageWebCoreEnd
