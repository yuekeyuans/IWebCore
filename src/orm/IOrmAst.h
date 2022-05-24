#pragma once

#include "base/IHeaderUtil.h"
#include "core/ast/IAstInterface.h"

$PackageWebCoreBegin

class IOrmAst : public IAstInterface
{
    Q_GADGET
    $AsAst(IOrmAst)
public:
    IOrmAst() = default;

    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
