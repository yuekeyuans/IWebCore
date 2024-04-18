#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/test/ITestManageBaseInterface.h"

$PackageWebCoreBegin

class IUnitTestManage : public ITestManageBaseInterface<IUnitTestManage>
{
public:
    IUnitTestManage() = default;
};

$PackageWebCoreEnd
