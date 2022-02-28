#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class INoCopyUnit
{
protected:
    INoCopyUnit() = default;
    ~INoCopyUnit() = default;

public:
    INoCopyUnit(const INoCopyUnit&) = delete;
    void operator=(const INoCopyUnit&) = delete;
};

$PackageWebCoreEnd
