#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/default/IStartupTaskInterface.h"

$PackageWebCoreBegin

class IBannerTask : public IStartupTaskInterface<IBannerTask>
{
    Q_GADGET
    $AsTask(IBannerTask)
public:
    IBannerTask() = default;

public:
    virtual void task() final;
};

$PackageWebCoreEnd
