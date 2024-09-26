#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/config/IConfigManageInterface.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

class IProfileManage final : public IConfigManageInterface, public ISingletonUnit<IProfileManage>
{
public:
    IProfileManage() = default;
};

$PackageWebCoreEnd
