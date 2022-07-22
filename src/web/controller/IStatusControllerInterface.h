#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/configuration/IConfigurationManage.h"
#include "core/task/IControllerTaskUnit.h"
#include "web/controller/IControllerManage.h"
#include "web/node/IStatusActionNode.h"

$PackageWebCoreBegin

namespace IStatusControllerInterfaceProxy
{
    void registerController(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaMethod>&methods);
    void registerError();

    void unRegisterController(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaMethod>&methods);
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

    auto clsInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    auto methods = IMetaUtil::getMetaMethods(T::staticMetaObject);
    IStatusControllerInterfaceProxy::registerController(this, clsInfo, methods);
}

template<typename T, bool enabled>
void IStatusControllerInterface<T, enabled>::unRegisterController()
{
    if(this != T::instance()){
        IStatusControllerInterfaceProxy::unRegisterError();
    }

    auto clsInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    auto methods = IMetaUtil::getMetaMethods(T::staticMetaObject);
    IStatusControllerInterfaceProxy::unRegisterController(this, clsInfo, methods);
}

$PackageWebCoreEnd
