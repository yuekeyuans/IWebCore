#pragma once

#include "base/IHeaderUtil.h"
#include "core/assert/IAssertInterface.h"

$PackageWebCoreBegin

class IFunctionNodeAssert : public IAssertInterface
{
    Q_GADGET
    $AsAssert(IFunctionNodeAssert)
public:
    IFunctionNodeAssert() = default;

    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
