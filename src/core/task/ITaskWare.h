#pragma once

#include "base/IHeaderUtil.h"
#include "core/unit/ISortUnit.h"

$PackageWebCoreBegin

class ITaskWare : public ISortUnit
{
    $AsWare
public:
    ITaskWare() = default;

public:
    virtual QString name() const = 0;
    virtual void task() = 0;
    virtual QString catagory() const = 0;
};

$PackageWebCoreEnd
