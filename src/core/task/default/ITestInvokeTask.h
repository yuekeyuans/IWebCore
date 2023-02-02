#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/ITaskWare.h"
#include "core/unit/IRegisterInstanceUnit.h"

$PackageWebCoreBegin

// special task
class ITestInvokeTask : public ITaskWare, public IRegisterInstanceUnit<ITestInvokeTask>
{
    Q_GADGET
    Q_DISABLE_COPY_MOVE(ITestInvokeTask)
    $AsTask(ITestInvokeTask)
private:
    ITestInvokeTask() = default;

public:
    virtual QString name() const override;
    virtual QString catagory() const override;
    virtual double order() const final;
    virtual void registerToBase() override;
    virtual void task() override;
};

$PackageWebCoreEnd
