#pragma once

#include "base/IHeaderUtil.h"
#include "core/assert/IAssertInterface.h"

$PackageWebCoreBegin

class IWebAst : public IAssertInterface
{
    Q_GADGET
    $AsAssert(IWebAst)
public:
    IWebAst() = default;

    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
