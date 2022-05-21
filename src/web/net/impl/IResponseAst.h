#pragma once

#include "base/IHeaderUtil.h"
#include "base/IJsonUtil.h"
#include "core/ast/IAstInterface.h"

$PackageWebCoreBegin

class IResponseAst : public IAstInterface
{
    Q_GADGET
    $AsAst(IResponseAst)
public:
    IResponseAst();

    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
