#pragma once

#include "INoCopyMoveUnit.h"
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IThreadUnit : INoCopyMoveUnit
{
protected:
    IThreadUnit() = default;
    ~IThreadUnit() = default;
};

$PackageWebCoreEnd
