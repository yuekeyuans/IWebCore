#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/configuration/IConfigurationManage.h"
#include "core/task/IControllerTaskUnit.h"
#include "web/controller/IControllerManage.h"
#include "web/node/IStatusFunctionNode.h"

$PackageWebCoreBegin

namespace IStatusControllerInterfaceProxy
{
    void registerController(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaMethod>&methods);
    void registerError();
}

template<typename T, bool enabled = true>
class IStatusControllerInterface : public IControllerTaskUnit<T, enabled>
{
protected:
    IStatusControllerInterface() = default;
    virtual ~IStatusControllerInterface() = default;

public:
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
    // TODO:
}

$PackageWebCoreEnd
