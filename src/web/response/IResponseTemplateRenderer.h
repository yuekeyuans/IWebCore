#pragma once

#include "core/base/IHeaderUtil.h"
#include "web/biscuits/IHttpStatus.h"

$PackageWebCoreBegin

class IResponseTemplateRenderer
{
public:
    enum PageType {
        Directory,
    };
public:
    IResponseTemplateRenderer();
    virtual ~IResponseTemplateRenderer() = default;

public:
    virtual bool isPathExist(const QString& path) = 0;
    virtual QString render(const QString& path, const QJsonObject& object) = 0;

    virtual QString getPage(IHttpStatus) = 0;
    virtual QString getPage(PageType) = 0;
};

$PackageWebCoreEnd
