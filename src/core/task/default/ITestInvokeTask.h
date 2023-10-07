#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/unit/ITaskWareUnit.h"

$PackageWebCoreBegin

// special task
class ITestInvokeTask : public ITaskWareUnit<ITestInvokeTask>
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
