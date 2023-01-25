#pragma once

#include <IWebCore>

// TODO: Configuration 的修改可以从这里开始

class GlobalConfiguration : public IConfigurationInterface<GlobalConfiguration>
{
    $AsConfiguration(GlobalConfiguration)
public:
    GlobalConfiguration() = default;

    virtual QJsonObject getConfigure() const override;
};

