#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/context/IContextTaskInterface.h"

$PackageWebCoreBegin

class IContextJsonConfigTask : public IContextTaskInterface<IContextJsonConfigTask>
{
    Q_GADGET
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
