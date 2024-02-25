#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IContextTaskInterface.h"
#include "core/config/IConfigPreProcessor.h"
#include "core/config/default/ILoadProfileFileUnit.h"

$PackageWebCoreBegin

class IContextYamlProfileTask : public IContextTaskInterface<IContextYamlProfileTask>, public ILoadProfileFileUnit
{
public:
    virtual QJsonValue config();

private:
    virtual double order() const final;
    virtual QStringList nameFilters() const final;
    QJsonValue parseYamlFile(const QString& path, bool&ok);

//    QStringList getYamlPaths();
//    QJsonObject parseYamlFile(const QString& path);
};

$PackageWebCoreEnd
