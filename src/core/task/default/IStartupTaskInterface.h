#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskManage.h"
#include "core/unit/IRegisterInstanceUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IStartupTaskInterface : public ITaskWare, public IRegisterInstanceUnit<T, enabled>
{
public:
    IStartupTaskInterface() = default;

public:
    virtual void task() = 0;

    virtual QString name() const override;
    virtual double order() const override;
    virtual QString catagory() const final;
    virtual void registerToBase() final;
};

template<typename T, bool enabled>
QString IStartupTaskInterface<T, enabled>::name() const
{
    return IMetaUtil::getMetaClassName(T::staticMetaObject);
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

template<typename T, bool enabled>
void IStartupTaskInterface<T, enabled>::registerToBase()
{
    ITaskManage::instance()->addTaskWare(T::instance());
}

$PackageWebCoreEnd
