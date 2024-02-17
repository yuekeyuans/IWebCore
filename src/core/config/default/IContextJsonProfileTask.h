#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IContextTaskInterface.h"
#include "core/config/IConfigPreProcessor.h"

$PackageWebCoreBegin

class IContextJsonProfileTask : public IContextTaskInterface<IContextJsonProfileTask>
{
    $AsProfile(IContextJsonProfileTask)
private:
    IContextJsonProfileTask() = default;

public:
    virtual QJsonValue getContext() final;

private:
    QStringList getJsonPaths();
    QJsonObject parseJsonFile(const QString& path);
};

$PackageWebCoreEnd
