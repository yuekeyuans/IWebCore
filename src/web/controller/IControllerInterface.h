#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/task/IControllerTaskUnit.h"
#include "web/controller/IControllerManage.h"

$PackageWebCoreBegin

struct IControllerInfo;

namespace IControllerInterfaceProxy
{
    void registerController(void* handler, const QString& className,
                            const QMap<QString, QString>& classMap, const QVector<QMetaMethod>& methods);
    void registerError();

    void unRegisterController(void* handler, const QString& className,
                              const QMap<QString, QString>& classMap, const QVector<QMetaMethod>& methods);
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

    auto className = IMetaUtil::getMetaClassName (T::staticMetaObject);
    auto classInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    auto classMethods = IMetaUtil::getMetaMethods(T::staticMetaObject);
    IControllerInterfaceProxy::registerController(this, className, classInfo, classMethods);
}

template<typename T, bool enabled>
void IControllerInterface<T, enabled>::unRegisterController()
{
    if(this !=  T::instance()){
        IControllerInterfaceProxy::unRegisterError();
    }

    auto className = IMetaUtil::getMetaClassName (T::staticMetaObject);
    auto classInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    auto classMethods = IMetaUtil::getMetaMethods(T::staticMetaObject);
    IControllerInterfaceProxy::unRegisterController(this, className, classInfo, classMethods);
}

$PackageWebCoreEnd
