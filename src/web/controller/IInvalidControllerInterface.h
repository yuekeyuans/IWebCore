#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

template<typename T, bool enable = true>
class IInvalidControllerInterface : public ITaskWareUnit<T, enabled>, public ISingletonUnit<T, enabled>
{
public:
    IInvalidControllerInterface() = default;

public:
    virtual QString name() const final;
    virtual QString catagory() const final;
    virtual void task() final;

};

template<typename T, bool enabled>
QString IInvalidControllerInterface<T, enabled>::name() const
{
    return IMetaUtil::getTypename<T>();
}

template<typename T, bool enabled>
QString IInvalidControllerInterface<T, enabled>::catagory() const
{
    return "Controller";
}

template<typename T, bool enabled>
void IInvalidControllerInterface<T, enabled>::task()
{
    // todo:
}

$PackageWebCoreEnd
