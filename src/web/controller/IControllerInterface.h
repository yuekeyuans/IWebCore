#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskManage.h"
#include "core/unit/IRegisterInstanceUnit.h"
#include "core/task/unit/IControllerTaskUnit.h"
#include "web/controller/IControllerManage.h"

$PackageWebCoreBegin

struct IControllerInfo;

template<typename T, bool enabled = true>
class IControllerInterface : public ITaskWare, public IRegisterInstanceUnit<T, enabled>
{
public:
    IControllerInterface() = default;

public:
    virtual QString name() const override;
    virtual QString catagory() const final;
    virtual void task() final;
    virtual void registerToBase();

    virtual void registerController() final;
    virtual void unRegisterController() final;
};


namespace IControllerInterfaceProxy
{
    void registerController(void* handler, const QString& className,
                            const QMap<QString, QString>& classMap, const QVector<QMetaMethod>& methods);
    void registerError();

    void unRegisterController(void* handler, const QString& className,
                              const QMap<QString, QString>& classMap, const QVector<QMetaMethod>& methods);
    void unRegisterError();
};

template<typename T, bool enabled>
QString IControllerInterface<T, enabled>::name() const
{
    return IMetaUtil::getMetaClassName(T::staticMetaObject);
}

template<typename T, bool enabled>
QString IControllerInterface<T, enabled>::catagory() const
{
    return "Controller";
}

template<typename T, bool enabled>
void IControllerInterface<T, enabled>::registerToBase()
{
    ITaskManage::instance()->addTaskWare(T::instance());
}

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
