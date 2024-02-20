#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/task/ITaskManage.h"
#include "core/task/unit/ITaskWareUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IStartupTaskInterface : public ITaskWareUnit<T, enabled>
{
public:
    IStartupTaskInterface() = default;

public:
    virtual void task() = 0;

    virtual QString name() const override;
    virtual double order() const override;
    virtual QString catagory() const final;
};

template<typename T, bool enabled>
QString IStartupTaskInterface<T, enabled>::name() const
{
    return IMetaUtil::getTypename<T>();
//    return IMetaUtil::getMetaClassName(T::staticMetaObject);
}

template<typename T, bool enabled>
double IStartupTaskInterface<T, enabled>::order() const
{
    return 50;
}

template<typename T, bool enabled>
QString IStartupTaskInterface<T, enabled>::catagory() const
{
    return "StartUp";
}

$PackageWebCoreEnd
