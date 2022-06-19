#pragma once

#include "base/IHeaderUtil.h"
#include "core/asset/IAssetInterface.h"

$PackageWebCoreBegin

class IOrmAst : public IAssetInterface
{
    Q_GADGET
    $AsAsset(IOrmAst)
public:
    IOrmAst() = default;

    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
