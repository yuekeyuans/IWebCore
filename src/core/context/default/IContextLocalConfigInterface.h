#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/context/IContextTaskInterface.h"
#include "core/context/IContextManage.h"

$PackageWebCoreBegin

template<typename T, bool enabled>
class IContextLocalConfigInterface : public IContextTaskInterface<T, enabled>
{
public:
    IContextLocalConfigInterface() = default;

public:
    virtual QJsonValue getSystemConfig() = 0;
    virtual QJsonValue getApplicationConfig() = 0;

protected:
    virtual void task() final;
};

template<typename T, bool enabled>
void IContextLocalConfigInterface<T, enabled>::task()
{
    auto systemConfig = getSystemConfig();
    IContextManage::addSystemConfig(systemConfig);

    auto applicationConfig = getApplicationConfig();
    IContextManage::addApplicationConfig(applicationConfig);
}

$PackageWebCoreEnd
