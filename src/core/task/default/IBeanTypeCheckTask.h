#pragma once
#include "core/util/IHeaderUtil.h"
#include "IStartupTaskInterface.h"

$PackageWebCoreBegin

class IBeanTypeCheckTask : public IStartupTaskInterface<IBeanTypeCheckTask>
{
private:
    virtual void task() final;
    virtual double order() const final;
};

$PackageWebCoreEnd
