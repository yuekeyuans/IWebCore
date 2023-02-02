#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/assert/IAssertInterface.h"

$PackageWebCoreBegin

class IRequestAssert : public IAssertInterface
{
    Q_GADGET
    $AsAssert(IRequestAssert)
public:
    IRequestAssert() = default;

    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
