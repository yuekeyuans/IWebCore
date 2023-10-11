#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/context/IContextTaskInterface.h"

$PackageWebCoreBegin

class IContextYamlConfigTask : public IContextTaskInterface<IContextYamlConfigTask>
{
    Q_GADGET
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
