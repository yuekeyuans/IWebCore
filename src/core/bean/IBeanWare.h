#pragma once

#include "base/IHeaderUtil.h"
#include "core/unit/IGadgetUnit.h"
#include "core/unit/IOrderUnit.h"

$PackageWebCoreBegin

class IBeanWare : public IGadgetUnit, public IOrderUnit
{
public:
    IBeanWare() = default;
    virtual ~IBeanWare() = default;
};

$PackageWebCoreEnd
