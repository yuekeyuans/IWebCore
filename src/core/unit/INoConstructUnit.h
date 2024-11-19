#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class INoConstructUnit
{
protected:
    INoConstructUnit() = default;
    ~INoConstructUnit() = default;
};

$PackageWebCoreEnd
