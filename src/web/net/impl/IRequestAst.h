#pragma once

#include "base/IHeaderUtil.h"
#include "core/ast/IAstInterface.h"

$PackageWebCoreBegin

class IRequestAst : public IAstInterface
{
    Q_GADGET
    $AsAst(IRequestAst)
public:
    IRequestAst() = default;

    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
