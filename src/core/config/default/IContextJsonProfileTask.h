#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IContextTaskInterface.h"
#include "core/config/IConfigPreProcessor.h"

$PackageWebCoreBegin

class IContextJsonProfileTask final: public IContextTaskInterface<IContextJsonProfileTask>
{
    $AsProfile(IContextJsonProfileTask)
private:
    IContextJsonProfileTask() = default;

public:
    virtual QJsonValue config() final;

private:
    QStringList getJsonPaths() const;
    QJsonObject parseJsonFile(const QString& path) const;
};

$PackageWebCoreEnd
