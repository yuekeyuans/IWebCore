#pragma once

#include "base/IHeaderUtil.h"
#include "core/asset/IAssetInterface.h"

$PackageWebCoreBegin

class IOrmAsset : public IAssetInterface
{
    Q_GADGET
    $AsAsset(IOrmAsset)
public:
    IOrmAsset() = default;

    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
