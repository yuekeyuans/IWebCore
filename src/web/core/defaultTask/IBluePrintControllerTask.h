#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/default/IEndupTaskInterface.h"

$PackageWebCoreBegin

class IBluePrintControllerTask : public IEndupTaskInterface<IBluePrintControllerTask>
{
public:
    IBluePrintControllerTask() = default;

public:
    virtual void task();
};

$PackageWebCoreEnd
