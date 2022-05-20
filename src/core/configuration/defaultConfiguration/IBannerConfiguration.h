#pragma once

#include "core/configuration/IConfigurationInterface.h"
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IBannerConfiguration : public  ISystemConfigurationInterface<IBannerConfiguration>
{
    $UseInstance(IBannerConfiguration)
public:
    IBannerConfiguration() = default;

    virtual QJsonObject getConfigure() const override;
};

$PackageWebCoreEnd
