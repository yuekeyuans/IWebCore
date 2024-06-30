#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/task/ITaskManage.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

struct IHttpControllerInfo;

template<typename T, bool enabled = true>
class IHttpControllerInterface : public ITaskWareUnit<T, enabled>, public ISingletonUnit<T>
{
public:
    IHttpControllerInterface() = default;

public:
    virtual QString name() const final;
    virtual QString catagory() const final;
    virtual void task() final;
};

namespace IControllerInterfaceHelper
{
    void registerController(void* handler, const QString& className,
                            const QMap<QString, QString>& classMap, const QVector<QMetaMethod>& methods);
    void registerError();
}

template<typename T, bool enabled>
QString IHttpControllerInterface<T, enabled>::name() const
{
    return IMetaUtil::getTypename<T>();
}

template<typename T, bool enabled>
QString IHttpControllerInterface<T, enabled>::catagory() const
{
    return "HttpController";
}

template<typename T, bool enabled>
void IHttpControllerInterface<T, enabled>::task()
{
    if(this != T::instance()){
        IControllerInterfaceHelper::registerError();
    }

    auto className = IMetaUtil::getMetaClassName (T::staticMetaObject);
    auto classInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    auto classMethods = IMetaUtil::getMetaMethods(T::staticMetaObject);
    IControllerInterfaceHelper::registerController(this, className, classInfo, classMethods);
}

$PackageWebCoreEnd
