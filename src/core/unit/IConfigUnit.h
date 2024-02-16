#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IToeUtil.h"
#include "core/base/IJsonUtil.h"

$PackageWebCoreBegin

template<typename T>
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

template<typename T>
void IConfigUnit<T>::addConfig(const QJsonValue &value, const QString &path)
{
    IJsonUtil::addToJsonObject(m_configs, path, value);
}

template<typename T>
QJsonValue IConfigUnit<T>::getConfig(const QString &path, bool *ok)
{
    return IJsonUtil::getJsonValue(m_configs, path, ok);
}

template<typename T>
bool IConfigUnit<T>::getConfigAsBool(const QString &path, bool *ok)
{
    auto value = getConfig(path, ok);
    if(ok){
        return value.toBool(ok);
    }
    return {};
}

template<typename T>
int IConfigUnit<T>::getConfigAsInt(const QString &path, bool *ok)
{
    auto value = getConfig(path, ok);
    if(ok){
        return value.toInt(ok);
    }
    return {};
}

template<typename T>
double IConfigUnit<T>::getConfigAsDouble(const QString &path, bool *ok)
{
    auto value = getConfig(path, ok);
    if(ok){
        return value.toDouble(ok);
    }
    return {};
}

template<typename T>
QString IConfigUnit<T>::getConfigAsString(const QString &path, bool *ok)
{
    auto value = getConfig(path, ok);
    return value.toString();
}

$PackageWebCoreEnd
