#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IContextTaskInterface.h"
#include "core/config/IContextPreProcessor.h"

$PackageWebCoreBegin

class IContextTomlConfigTask : public IContextTaskInterface<IContextTomlConfigTask>
{
    $AsContext(IContextTomlConfigTask)
private:
    IContextTomlConfigTask() = default;

public:
    virtual QJsonValue getApplicationConfig();
};

$PackageWebCoreEnd
