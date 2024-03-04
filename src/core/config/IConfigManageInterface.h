#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "core/result/IResult.h"

$PackageWebCoreBegin

class IConfigManageInterface
{
public:
    void addConfig(const QJsonValue& value, const QString& path="");

    QJsonValue getConfig(const QString& path, bool& ok);
    IResult<QJsonValue> getConfig(const QString& path);

    bool getConfigAsBool(const QString& path, bool& ok);
    IResult<bool> getConfigAsBool(const QString& path);

    int getConfigAsInt(const QString& path, bool& ok);
    IResult<int> getConfigAsInt(const QString& path);

    double getConfigAsDouble(const QString& path, bool& ok);
    IResult<double> getConfigAsDouble(const QString& path);

    QString getConfigAsString(const QString& path, bool& ok);
    IResult<QString> getConfigAsString(const QString& path);

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
