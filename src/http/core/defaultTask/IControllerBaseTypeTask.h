#pragma once

#include "core/util/IPackageUtil.h"
#include "core/task/unit/ITaskInstantUnit.h"

$PackageWebCoreBegin

class IControllerBaseTypeTask : public ITaskInstantUnit<IControllerBaseTypeTask, true>
{
public:
    IControllerBaseTypeTask() = default;

public:
    virtual void task() final;
};

$PackageWebCoreEnd
