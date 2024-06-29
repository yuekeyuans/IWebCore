#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "core/task/ITaskManage.h"
#include "core/task/unit/ITaskWareUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IStartupTaskInterface : public ITaskWareUnit<T, enabled>, public ISingletonUnit<T>
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
    return IMetaUtil::getBareTypeName<T>();
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
