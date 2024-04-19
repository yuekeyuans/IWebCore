#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/test/ITestBaseInterface.h"
#include "web/core/test/IHttpTestManage.h"
#include "web/core/test/IHttpTestInterface.h"
#include "web/core/test/IHttpTestAnnomacro.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IHttpTestInterface : public ITestBaseInterface<T, IHttpTestManage, enabled>
{
public:
    IHttpTestInterface() = default;
};

$PackageWebCoreEnd
