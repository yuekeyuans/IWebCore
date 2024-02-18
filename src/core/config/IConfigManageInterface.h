#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IConfigManageInterface
{
public:
    IConfigManageInterface() = default;

public:
    void addConfig(const QJsonValue& value, const QString& path="");

    QJsonValue getConfig(const QString& path, bool* ok);
    bool getConfigAsBool(const QString& path, bool* ok);
    int getConfigAsInt(const QString& path, bool* ok);
    double getConfigAsDouble(const QString& path, bool* ok);
    QString getConfigAsString(const QString& path, bool* ok);

protected:
    QJsonObject m_configs;
};

$PackageWebCoreEnd
