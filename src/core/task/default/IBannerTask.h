#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/default/IStartupTaskInterface.h"

$PackageWebCoreBegin

class IBannerTask : public IStartupTaskInterface<IBannerTask>
{
private:
    virtual void $task() final;
    virtual double $order() const final;
};

$PackageWebCoreEnd
