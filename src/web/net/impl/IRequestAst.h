#pragma once

#include "base/IHeaderUtil.h"
#include "core/asset/IAssetInterface.h"

$PackageWebCoreBegin

class IRequestAst : public IAssetInterface
{
    Q_GADGET
    $AsAsset(IRequestAst)
public:
    IRequestAst() = default;

    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
