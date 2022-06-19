#pragma once

#include "base/IHeaderUtil.h"
#include "core/assert/IAssertInterface.h"

$PackageWebCoreBegin

class IFunctionNodeAst : public IAssertInterface
{
    Q_GADGET
    $AsAssert(IFunctionNodeAst)
public:
    IFunctionNodeAst() = default;

    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
