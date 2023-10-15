#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/context/IContextTaskInterface.h"
#include "core/context/IContextPreProcessor.h"

$PackageWebCoreBegin

class IContextSystemVariableTask : public IContextTaskInterface<IContextSystemVariableTask>
{
    $AsContext(IContextSystemVariableTask)
private:
    IContextSystemVariableTask() = default;

public:
    virtual QJsonValue getSystemConfig();

private:
    QJsonObject getSystemEnvironment();
};

$PackageWebCoreEnd

