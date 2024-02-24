#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IContextTaskInterface.h"
#include "core/config/IConfigPreProcessor.h"

$PackageWebCoreBegin

class IContextYamlProfileTask : public IContextTaskInterface<IContextYamlProfileTask>
{
public:
    virtual QJsonValue config();

private:
    virtual double order() const final;
    QStringList getYamlPaths();
    QJsonObject parseYamlFile(const QString& path);
};

$PackageWebCoreEnd
