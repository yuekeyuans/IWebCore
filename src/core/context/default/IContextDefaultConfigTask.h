#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/context/IContextTaskInterface.h"

$PackageWebCoreBegin

class IContextDefaultConfigTask : public IContextTaskInterface<IContextDefaultConfigTask>
{
    Q_GADGET
    $AsContext(IContextDefaultConfigTask)
private:
    IContextDefaultConfigTask() = default;

public:
    virtual void task() final;
};

$PackageWebCoreEnd
