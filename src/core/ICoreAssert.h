#pragma once

#include "base/IHeaderUtil.h"
#include "core/assert/IAssertInterface.h"

$PackageWebCoreBegin

class ICoreAssert : public IAssertInterface
{
    Q_GADGET
    $AsAssert(ICoreAssert)
public:
    ICoreAssert() = default;

public:
    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
