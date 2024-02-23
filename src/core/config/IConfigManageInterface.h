#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

class IConfigManageInterface
{
public:
    void addConfig(const QJsonValue& value, const QString& path="");

    QJsonValue getConfig(const QString& path, bool& ok);

    bool getConfigAsBool(const QString& path, bool& ok);
    int getConfigAsInt(const QString& path, bool& ok);
    double getConfigAsDouble(const QString& path, bool& ok);
    QString getConfigAsString(const QString& path, bool& ok);

    template<typename T>
    T getBean(const QString& path, bool& ok);

protected:
    QJsonObject m_configs;
};

template<typename T>
T IConfigManageInterface::getBean(const QString& path, bool& ok)
{
    auto value = getConfig(path, ok);
    if(ok){
         return T::fromJson(value.toObject());
    }

    return {};
}

$PackageWebCoreEnd
