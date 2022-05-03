#pragma once

#include "base/IHeaderUtil.h"
#include "common/support/INoCopyMoveUnit.h"

$PackageWebCoreBegin

class IThreadUnit : INoCopyMoveUnit
{
protected:
    IThreadUnit() = default;
    ~IThreadUnit() = default;
};

$PackageWebCoreEnd
