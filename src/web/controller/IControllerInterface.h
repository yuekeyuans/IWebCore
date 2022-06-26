#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/task/IControllerTaskUnit.h"
#include "web/controller/IControllerManage.h"
#include "web/node/IUrlFunctionNode.h"

$PackageWebCoreBegin

namespace IControllerInterfaceProxy
{
    void registerController(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaMethod>&methods);
    void registerError();

    void unRegisterController(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaMethod>&methods);
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

    auto clsInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    auto methods = IMetaUtil::getMetaMethods(T::staticMetaObject);
    IControllerInterfaceProxy::registerController(this, clsInfo, methods);
}

template<typename T, bool enabled>
void IControllerInterface<T, enabled>::unRegisterController()
{
    if(this !=  T::instance()){
        IControllerInterfaceProxy::unRegisterError();
    }

    auto clsInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    auto methods = IMetaUtil::getMetaMethods(T::staticMetaObject);
    IControllerInterfaceProxy::unRegisterController(this, clsInfo, methods);
}

$PackageWebCoreEnd
