#pragma once

#include "core/util/IPackageUtil.h"
#include "core/task/unit/ITaskInstantUnit.h"

$PackageWebCoreBegin

class IRegisterBaseTypeTask : public ITaskInstantUnit<IRegisterBaseTypeTask, true>
{
public:
    IRegisterBaseTypeTask() = default;

public:
    virtual void task() final;
};

$PackageWebCoreEnd
