#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/assert/IAssertInterface.h"

$PackageWebCoreBegin

class IHttpAssert : public IAssertInterface
{
    $AsAssert(IHttpAssert)
private:
    IHttpAssert() = default;
    virtual void loadAssert() final;
};

$PackageWebCoreEnd
