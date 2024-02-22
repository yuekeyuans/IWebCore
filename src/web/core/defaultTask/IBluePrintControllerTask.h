#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/default/IEndupTaskInterface.h"

$PackageWebCoreBegin

class IBluePrintControllerTask : public IEndupTaskInterface<IBluePrintControllerTask>
{
    friend class ISingletonUnit<IBluePrintControllerTask>;
private:
    IBluePrintControllerTask() = default;

public:
    virtual void task();
};

$PackageWebCoreEnd
