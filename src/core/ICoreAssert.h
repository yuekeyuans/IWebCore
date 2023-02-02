#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/assert/IAssertInterface.h"

$PackageWebCoreBegin

class ICoreAssert : public IAssertInterface
{
    Q_GADGET
    $AsAssert(ICoreAssert)
public:
    ICoreAssert() = default;

private:
    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
