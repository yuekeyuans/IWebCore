#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/unit/IManagedTaskWareUnit.h"

$PackageWebCoreBegin

// special task
class ITestInvokeTask : public IManagedTaskWareUnit<ITestInvokeTask>
{
    Q_GADGET
    $AsTask(ITestInvokeTask)
private:
    ITestInvokeTask() = default;

public:
    virtual QString name() const override;
    virtual QString catagory() const override;
    virtual double order() const final;
    virtual void task() override;
};

$PackageWebCoreEnd
