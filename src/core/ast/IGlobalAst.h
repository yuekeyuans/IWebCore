#pragma once

#include "IAstInterface.h"
#include "IAstPreProcessor.h"
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IGlobalAst : public IAstInterface
{
    Q_GADGET
    $AsAst(IGlobalAst)
public:
    IGlobalAst();

public:
    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
