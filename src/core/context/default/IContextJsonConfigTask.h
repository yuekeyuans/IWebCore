#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/context/IContextTaskInterface.h"

$PackageWebCoreBegin

class IContextJsonConfigTask : public IContextTaskInterface<IContextJsonConfigTask>
{
    Q_GADGET
    $AsContext(IContextTaskInterface)
private:
    IContextJsonConfigTask() = default;

public:
    virtual void task() final;
};

$PackageWebCoreEnd
