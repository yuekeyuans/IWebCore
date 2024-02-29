#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/default/IInitializationTaskInterface.h"

$PackageWebCoreBegin

class IStaticFileServiceTask : public IInitializationTaskInterface<IStaticFileServiceTask>
{
public:
    IStaticFileServiceTask() = default;

protected:
    virtual void task() final;
};

$PackageWebCoreEnd
