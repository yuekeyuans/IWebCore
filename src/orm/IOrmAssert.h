#pragma once

#include "base/IHeaderUtil.h"
#include "core/assert/IAssertInterface.h"

$PackageWebCoreBegin

class IOrmAssert : public IAssertInterface
{
    Q_GADGET
    $AsAssert(IOrmAssert)
public:
    IOrmAssert() = default;

    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
