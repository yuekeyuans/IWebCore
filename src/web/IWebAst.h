#pragma once

#include "base/IHeaderUtil.h"
#include "core/ast/IAstInterface.h"

$PackageWebCoreBegin

class IWebAst : public IAstInterface
{
    Q_GADGET
    $AsAst(IWebAst)
public:
    IWebAst() = default;

    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
