#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/config/IContextTaskInterface.h"
#include "core/config/IConfigPreProcessor.h"

$PackageWebCoreBegin

class IContextSystemVariableTask : public IContextTaskInterface<IContextSystemVariableTask, false>
{
public:
    virtual QJsonValue config();

private:
    QJsonObject getSystemEnvironment();
};

$PackageWebCoreEnd

