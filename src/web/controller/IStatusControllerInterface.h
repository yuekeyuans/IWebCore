#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/configuration/IConfigurationManage.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskManage.h"
//#include "core/task/unit/IControllerTaskUnit.h"
#include "core/unit/IRegisterInstanceUnit.h"
#include "web/controller/IControllerManage.h"
#include "web/node/IStatusActionNode.h"

$PackageWebCoreBegin

struct IControllerInfo;

template<typename T, bool enabled = true>
class IStatusControllerInterface : public ITaskWare, public IRegisterInstanceUnit<T, enabled>
{
public:
    IStatusControllerInterface() = default;
    virtual ~IStatusControllerInterface() = default;

    virtual QString name() const override;
    virtual QString catagory() const override;
    virtual void registerToBase();
    virtual void task() final;

public:
    virtual void registerController() final;
    virtual void unRegisterController() final;
};

namespace IStatusControllerInterfaceProxy
{
    void registerController(void* handler, const QString& className,
                            const QMap<QString, QString>& classInfo, const QVector<QMetaMethod>& methods);
    void registerError();

    void unRegisterController(void* handler, const QString& className,
                              const QMap<QString, QString>& classInfo, const QVector<QMetaMethod>& methods);
    void unRegisterError();
}

template<typename T, bool enabled>
QString IStatusControllerInterface<T, enabled>::name() const
{
    return IMetaUtil::getMetaClassName(T::staticMetaObject);
}

template<typename T, bool enabled>
QString IStatusControllerInterface<T, enabled>::catagory() const
{
    return "Controller";
}

template<typename T, bool enabled>
void IStatusControllerInterface<T, enabled>::registerToBase()
{
    ITaskManage::instance()->addTaskWare(T::instance());
}

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

    auto className = IMetaUtil::getMetaClassName (T::staticMetaObject);
    auto classInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    auto classMethods = IMetaUtil::getMetaMethods(T::staticMetaObject);
    IStatusControllerInterfaceProxy::registerController(this, className, classInfo, classMethods);
}

template<typename T, bool enabled>
void IStatusControllerInterface<T, enabled>::unRegisterController()
{
    if(this != T::instance()){
        IStatusControllerInterfaceProxy::unRegisterError();
    }

    auto className = IMetaUtil::getMetaClassName (T::staticMetaObject);
    auto classInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    auto classMethods = IMetaUtil::getMetaMethods(T::staticMetaObject);
    IStatusControllerInterfaceProxy::unRegisterController(this, className, classInfo, classMethods);
}

$PackageWebCoreEnd
