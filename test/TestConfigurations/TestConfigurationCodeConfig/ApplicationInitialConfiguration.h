#pragma once

#include <IWebCore>

// 使用代码的方式加载 配置
class ApplicationInitialConfiguration : public IConfigurationInterface<ApplicationInitialConfiguration>
{
    $AsConfiguration(ApplicationInitialConfiguration)
public:
    ApplicationInitialConfiguration();
    virtual QJsonObject getConfigure() const override;
};
