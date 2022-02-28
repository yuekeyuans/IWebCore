#pragma once

#include "base/IHeaderUtil.h"
#include "configuration/IConfigurationInterface.h"

$PackageWebCoreBegin

class IBannerConfiguration : public  ISystemConfigurationInterface<IBannerConfiguration>
{
    $UseInstance(IBannerConfiguration)
public:
    IBannerConfiguration() = default;

    virtual QJsonObject getConfigure() const override;
};

$PackageWebCoreEnd
