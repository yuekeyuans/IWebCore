#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/IConfigUnit.h"

$PackageWebCoreBegin

class IProfileManage : public IConfigUnit
{
    $UseInstance(IProfileManage)
private:
    IProfileManage() = default;
};

$PackageWebCoreEnd
