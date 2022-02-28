#pragma once

#include <IWebCore>

class GlobalConfiguration : public IConfigurationInterface<GlobalConfiguration>
{
    $AsConfiguration(GlobalConfiguration)
public:
    GlobalConfiguration() = default;

    virtual QJsonObject getConfigure() const override;
};

