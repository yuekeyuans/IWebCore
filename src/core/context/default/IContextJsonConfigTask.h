#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/context/IContextTaskInterface.h"
#include "core/context/IContextPreProcessor.h"

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
