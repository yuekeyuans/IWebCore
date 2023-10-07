#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/IGadgetUnit.h"
#include "core/unit/IOrderUnit.h"

$PackageWebCoreBegin

class IBeanWare : public IGadgetUnit
{
public:
    IBeanWare() = default;
    virtual ~IBeanWare() = default;

public:
    virtual QString name() const = 0;
};

$PackageWebCoreEnd
