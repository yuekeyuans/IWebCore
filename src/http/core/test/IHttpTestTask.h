#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/test/ITestTaskBaseInterface.h"
#include "http/core/test/IHttpTestManage.h"

$PackageWebCoreBegin

class IHttpTestTask : public ITestTaskBaseInterface<IHttpTestTask, IHttpTestManage>
{
public:
    IHttpTestTask() = default;

public:
    virtual void task() final;
};

$PackageWebCoreEnd
