#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IContextTaskInterface.h"
#include "core/config/IContextPreProcessor.h"

$PackageWebCoreBegin

class IContextJsonConfigTask : public IContextTaskInterface<IContextJsonConfigTask>
{
    $AsContext(IContextJsonConfigTask)
private:
    IContextJsonConfigTask() = default;

public:
    virtual QJsonValue getApplicationConfig();

private:
    QStringList getJsonPaths();
    QJsonObject parseJsonFile(const QString& path);
};

$PackageWebCoreEnd
