#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class INoConstructUnit
{
protected:
    INoConstructUnit() = default;
    ~INoConstructUnit() = default;
};

$PackageWebCoreEnd
