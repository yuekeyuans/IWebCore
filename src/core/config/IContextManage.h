#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/config/IConfigManageInterface.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

class IContextManage final : public IConfigManageInterface, public ISingletonUnit<IContextManage>
{
public:
    IContextManage() = default;
};

$PackageWebCoreEnd
