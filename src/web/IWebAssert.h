#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/assert/IAssertInterface.h"

$PackageWebCoreBegin

class IWebAssert : public IAssertInterface
{
    $AsAssert(IWebAssert)
private:
    IWebAssert() = default;
    virtual void loadAssert() final;
};

$PackageWebCoreEnd
