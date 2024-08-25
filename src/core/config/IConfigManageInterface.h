#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "core/base/IResult.h"

$PackageWebCoreBegin

class IConfigManageInterface
{
public:
    void addConfig(const IJson& value, const QString& path="");

    IJson getConfig(const QString& path);
//    IResult<IJson> getConfig(const QString& path);

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
//    QJsonObject m_configs;
    IJson m_configs;
};

template<typename T>
T IConfigManageInterface::getBean(const QString& path, bool& ok)
{
//    auto value = getConfig(path, ok);
//    if(ok){
//         return T::fromJson(value.toObject());
//    }

    return {};
}

$PackageWebCoreEnd
