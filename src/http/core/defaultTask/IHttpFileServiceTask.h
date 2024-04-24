#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/default/IInitializationTaskInterface.h"

$PackageWebCoreBegin

class IHttpFileServiceTask : public IInitializationTaskInterface<IHttpFileServiceTask>
{
public:
    IHttpFileServiceTask() = default;

protected:
    virtual void task() final;
};

$PackageWebCoreEnd
