#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/context/IContextTaskInterface.h"

$PackageWebCoreBegin

class IContextSystemVariableTask : public IContextTaskInterface<IContextSystemVariableTask>
{
    Q_GADGET
    $AsContext(IContextSystemVariableTask)
private:
    IContextSystemVariableTask();

public:
    virtual void task() final;
};

