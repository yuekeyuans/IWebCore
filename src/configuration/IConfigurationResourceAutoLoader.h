#pragma once

#include "base/IHeaderUtil.h"
#include "configuration/IConfigurationTaskInterface.h"
#include "common/support/IRegisterInstanceUnit.h"

$PackageWebCoreBegin

/**
 * 自动加载资源文件， json 类型文件， yaml 类型文件 两种配置
 */
class IConfigurationResourceAutoLoader : public IConfigurationTaskInterface<IConfigurationResourceAutoLoader>
{
    $UseInstance(IConfigurationResourceAutoLoader)
private:
    IConfigurationResourceAutoLoader() = default;

public:
    virtual QString taskFinishTip() final;
    virtual void task() final;

private:
    static void loadSystemEnvironment();
    static void loadJson();
    static void loadYaml();
};


$PackageWebCoreEnd
