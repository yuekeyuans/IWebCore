#pragma once

#include "IGadgetUnit.h"
#include "core/unit/IOrderUnit.h"
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IBeanWare : public IGadgetUnit, public IOrderUnit
{
public:
    IBeanWare() = default;
    virtual ~IBeanWare() = default;
};

$PackageWebCoreEnd
