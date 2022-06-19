#pragma once

#include "base/IHeaderUtil.h"
#include "core/asset/IAssetInterface.h"

$PackageWebCoreBegin

class IFunctionNodeAst : public IAssetInterface
{
    Q_GADGET
    $AsAsset(IFunctionNodeAst)
public:
    IFunctionNodeAst() = default;

    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
