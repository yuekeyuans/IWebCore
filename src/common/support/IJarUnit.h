#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IJarUnit
{
public:
    IJarUnit() = default;
    virtual bool isValid() const;
};

$PackageWebCoreEnd
