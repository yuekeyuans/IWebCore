#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/default/IEndupTaskInterface.h"

$PackageWebCoreBegin

class IHttpPrintTraceTask : public IEndupTaskInterface<IHttpPrintTraceTask>
{
public:
    IHttpPrintTraceTask() = default;

public:
    virtual void task();
};

$PackageWebCoreEnd
