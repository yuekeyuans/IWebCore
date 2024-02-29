#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IInitializationTaskInterface : public ITaskWareUnit<T, enabled>, public ISingletonUnit<T>
{
public:
    IInitializationTaskInterface() = default;

public:
    virtual void task() = 0;

protected:
    virtual QString name() const final;
    virtual QString catagory() const final;
};

template<typename T, bool enabled>
QString IInitializationTaskInterface<T, enabled>::name() const
{
    return IMetaUtil::getTypename<T>();
}

template<typename T, bool enabled>
QString IInitializationTaskInterface<T, enabled>::catagory() const
{
    return "Initialization";
}

$PackageWebCoreEnd
