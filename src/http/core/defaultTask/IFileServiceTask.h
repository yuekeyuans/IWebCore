#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/default/IInitializationTaskInterface.h"

$PackageWebCoreBegin

class IFileServiceTask : public IInitializationTaskInterface<IFileServiceTask>
{
public:
    IFileServiceTask() = default;

protected:
    virtual void task() final;
};

$PackageWebCoreEnd
