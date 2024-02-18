#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IContextTaskInterface.h"
#include "core/config/IConfigPreProcessor.h"

$PackageWebCoreBegin

class IContextSystemVariableTask : public IContextTaskInterface<IContextSystemVariableTask, false>
{
    $AsContext(IContextSystemVariableTask)
private:
    IContextSystemVariableTask() = default;

public:
    virtual QJsonValue config();

private:
    QJsonObject getSystemEnvironment();
};

$PackageWebCoreEnd

