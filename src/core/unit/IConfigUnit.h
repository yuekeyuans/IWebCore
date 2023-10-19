#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IConfigUnit
{
public:
    IConfigUnit() = default;

public:
    void addConfig(const QJsonValue& value, const QString& path="");

    QJsonValue getConfig(const QString& path, bool* ok=nullptr);
    bool getConfigAsBool(const QString& path, bool* ok=nullptr);
    int getConfigAsInt(const QString& path, bool* ok=nullptr);
    double getConfigAsDouble(const QString& path, bool* ok=nullptr);
    QString getConfigAsString(const QString& path, bool* ok=nullptr);

protected:
    QJsonObject m_configs;

};

$PackageWebCoreEnd
