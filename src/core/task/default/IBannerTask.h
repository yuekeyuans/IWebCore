#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/default/IStartupTaskInterface.h"

$PackageWebCoreBegin

class IBannerTask : public IStartupTaskInterface<IBannerTask>
{
    Q_GADGET
    $AsTask(IBannerTask)
private:
    IBannerTask() = default;

private:
    virtual void task() final;
    virtual double order() const final;
};

$PackageWebCoreEnd
