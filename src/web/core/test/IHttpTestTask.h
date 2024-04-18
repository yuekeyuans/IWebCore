#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/test/ITestTaskBaseInterface.h"
#include "web/core/test/IHttpTestManage.h"

$PackageWebCoreBegin

class IHttpTestTask : public ITestTaskBaseInterface<IHttpTestTask, IHttpTestManage>
{
public:
    IHttpTestTask() = default;
};

$PackageWebCoreEnd
