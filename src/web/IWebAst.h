#pragma once

#include "base/IHeaderUtil.h"
#include "core/asset/IAssetInterface.h"

$PackageWebCoreBegin

class IWebAst : public IAssetInterface
{
    Q_GADGET
    $AsAsset(IWebAst)
public:
    IWebAst() = default;

    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
