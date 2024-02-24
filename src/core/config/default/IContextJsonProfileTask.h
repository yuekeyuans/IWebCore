#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IContextTaskInterface.h"
#include "core/config/IConfigPreProcessor.h"

$PackageWebCoreBegin

class IContextJsonProfileTask final: public IContextTaskInterface<IContextJsonProfileTask>
{
public:
    virtual QJsonValue config() final;

private:
    virtual double order() const;
    QStringList getConfigDirs() const;
    QStringList getJsonPaths() const;
    QStringList getValidatedJsonPaths() const;
    QJsonObject parseJsonFile(const QString& path) const;    
};

$PackageWebCoreEnd
