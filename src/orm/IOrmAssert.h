#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/assert/IAssertInterface.h"

$PackageWebCoreBegin

class IOrmAssert : public IAssertInterface
{
    $AsAssert(IOrmAssert)
private:
    IOrmAssert() = default;
    virtual void loadAssert() final;
};

$PackageWebCoreEnd
