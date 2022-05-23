#pragma once

#include "base/IHeaderUtil.h"
#include "core/ast/IAstInterface.h"

$PackageWebCoreBegin

class IFunctionNodeAst : public IAstInterface
{
    Q_GADGET
    $AsAst(IFunctionNodeAst)
public:
    IFunctionNodeAst() = default;

    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
