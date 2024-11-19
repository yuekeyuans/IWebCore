#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/assert/IAssertInterface.h"

$PackageWebCoreBegin

class IOrmAssert1 : public IAssertInterface
{
    $AsAssert(IOrmAssert1)
private:
    IOrmAssert1() = default;
    virtual void loadAssert() final;
};

$PackageWebCoreEnd
