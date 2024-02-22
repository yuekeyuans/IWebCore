#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "core/task/unit/ITaskWareUnit.h"

$PackageWebCoreBegin

// special task
class ITestInvokeTask : public ITaskWareUnit<ITestInvokeTask>, public ISingletonUnit<ITestInvokeTask>
{
public:
    ITestInvokeTask() = default;

public:
    virtual QString name() const override;
    virtual QString catagory() const override;
    virtual double order() const final;
    virtual void task() override;
};

$PackageWebCoreEnd
