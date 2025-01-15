#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/default/IInitializationTaskInterface.h"

$PackageWebCoreBegin

// TODO: this will be moved to plugin latter

class IHttpFileServiceTask : public IInitializationTaskInterface<IHttpFileServiceTask>
{
public:
    IHttpFileServiceTask() = default;

protected:
    virtual void $task() final;
};

$PackageWebCoreEnd
