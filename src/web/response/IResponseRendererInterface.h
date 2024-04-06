#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IResponseRendererInterface
{
public:
    IResponseRendererInterface() = default;
    virtual ~IResponseRendererInterface() = default;

public:
    virtual bool isPathExist(const QString& path) = 0;
    virtual QString render(const QString& path, const QJsonObject& object) = 0;
};

$PackageWebCoreEnd
