#pragma once

#include "base/IHeaderUtil.h"
#include "core/assert/IAssertInterface.h"

$PackageWebCoreBegin

class IWebAssert : public IAssertInterface
{
    Q_GADGET
    $AsAssert(IWebAssert)
public:
    IWebAssert() = default;

    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
