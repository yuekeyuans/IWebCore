#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/assert/IAssertInterface.h"

$PackageWebCoreBegin

class IHttpAssert1 : public IAssertInterface
{
    $AsAssert(IHttpAssert1)
private:
    IHttpAssert1() = default;
    virtual void loadAssert() final;
};

$PackageWebCoreEnd
