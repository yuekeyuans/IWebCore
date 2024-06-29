#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/test/ITestManageBaseInterface.h"
#include "core/task/unit/ITaskWareUnit.h"

$PackageWebCoreBegin

template<typename T, typename Manage, bool enabled =true>
class ITestBaseInterface : public ITaskWareUnit<T, enabled>, public QObject, public ISingletonUnit<T>
{
public:
    ITestBaseInterface() = default;

public:
    virtual QString name() const override;
    virtual QString catagory() const override;
    virtual void registerToBase() final;
    virtual void task() final;
};

template<typename T, typename Manage,  bool enabled>
QString ITestBaseInterface<T, Manage, enabled>::name() const
{
    return IMetaUtil::getMetaClassName(T::staticMetaObject);
}

template<typename T, typename Manage, bool enabled>
QString ITestBaseInterface<T, Manage, enabled>::catagory() const
{
    return "Test";
}

template<typename T, typename Manage, bool enabled>
void ITestBaseInterface<T, Manage, enabled>::registerToBase()
{
    ITaskManage::instance()->addTaskWare(T::instance());
}

template<typename T, typename Manage, bool enabled>
void ITestBaseInterface<T, Manage, enabled>::task()
{
    Manage::instance()->addTest(T::instance());
}

$PackageWebCoreEnd
