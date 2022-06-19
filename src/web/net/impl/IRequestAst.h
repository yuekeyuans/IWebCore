#pragma once

#include "base/IHeaderUtil.h"
#include "core/assert/IAssertInterface.h"

$PackageWebCoreBegin

class IRequestAst : public IAssertInterface
{
    Q_GADGET
    $AsAssert(IRequestAst)
public:
    IRequestAst() = default;

    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
