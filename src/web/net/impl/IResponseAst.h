#pragma once

#include "base/IHeaderUtil.h"
#include "base/IJsonUtil.h"
#include "core/ast/IAstInterface.h"

$PackageWebCoreBegin

class IResponseAst : public IAstInterface
{
    $AsAst(IResponseAst)
public:
    IResponseAst();

};

$PackageWebCoreEnd
