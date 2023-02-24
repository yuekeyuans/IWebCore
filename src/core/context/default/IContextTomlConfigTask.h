#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/context/IContextTaskInterface.h"

$PackageWebCoreBegin

class IContextTomlConfigTask : public IContextTaskInterface<IContextTomlConfigTask>
{
    Q_GADGET
    $AsContext(IContextTomlConfigTask)
private:
    IContextTomlConfigTask();

public:
    virtual void task() final;
};

