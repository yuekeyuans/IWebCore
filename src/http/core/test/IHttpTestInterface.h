#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/test/ITestBaseInterface.h"
#include "http/core/test/IHttpTestManage.h"
#include "http/core/test/IHttpTestInterface.h"
#include "http/core/test/IHttpTestTool.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IHttpTestInterface : public ITestBaseInterface<T, IHttpTestManage, enabled>, public IHttpTestTool
{
public:
    IHttpTestInterface() = default;
};

$PackageWebCoreEnd
