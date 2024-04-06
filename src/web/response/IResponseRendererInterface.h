#pragma once

#include "core/base/IHeaderUtil.h"
#include "web/biscuits/IHttpStatus.h"

$PackageWebCoreBegin

class IResponseRendererInterface
{
public:
    IResponseRendererInterface();
    virtual ~IResponseRendererInterface() = default;

public:
    virtual bool isPathExist(const QString& path) = 0;
    virtual QString render(const QString& path, const QJsonObject& object) = 0;
    virtual QString getStatusPage(IHttpStatus) = 0;
    virtual QString getDefaultPage(const QString& pageType) = 0;
};

$PackageWebCoreEnd
