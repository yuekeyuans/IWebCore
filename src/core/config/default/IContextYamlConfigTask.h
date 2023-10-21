#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IContextTaskInterface.h"
#include "core/config/IContextPreProcessor.h"

$PackageWebCoreBegin

class IContextYamlConfigTask : public IContextTaskInterface<IContextYamlConfigTask>
{
    $AsContext(IContextYamlConfigTask)
private:
    IContextYamlConfigTask() = default;

public:
    virtual QJsonValue getApplicationConfig();

private:
    QStringList getYamlPaths();
    QJsonObject parseYamlFile(const QString& path);
};

$PackageWebCoreEnd
