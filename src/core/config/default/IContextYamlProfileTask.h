#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IContextTaskInterface.h"
#include "core/config/IConfigPreProcessor.h"

$PackageWebCoreBegin

class IContextYamlProfileTask : public IContextTaskInterface<IContextYamlProfileTask>
{
    $AsProfile(IContextYamlProfileTask)
private:
    IContextYamlProfileTask() = default;

public:
    virtual QJsonValue getContext();

private:
    QStringList getYamlPaths();
    QJsonObject parseYamlFile(const QString& path);
};

$PackageWebCoreEnd
