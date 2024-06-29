#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/test/ITestBaseInterface.h"
#include "core/test/IUnitTestManage.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IUnitTestInterface : public ITestBaseInterface<T, IUnitTestManage, enabled>
{
public:
    IUnitTestInterface() = default;
};

$PackageWebCoreEnd
