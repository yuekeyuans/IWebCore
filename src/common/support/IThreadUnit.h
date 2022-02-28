#pragma once

#include "base/IHeaderUtil.h"
#include "common/support/INoCopyUnit.h"

$PackageWebCoreBegin

class IThreadUnit : INoCopyUnit
{
protected:
    IThreadUnit() = default;
    ~IThreadUnit() = default;
};

$PackageWebCoreEnd
