#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/context/IContextTaskInterface.h"
#include "core/context/IContextPreProcessor.h"

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
