#pragma once

#include "IConfigurationPreProcessor.h"
#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

extern const char SystemConfigurationGroup[];
extern const char ApplicationConfigurationGroup[];


class ITaskManage;

class IContextManage
{
    $UseInstance(IContextManage)
private:
    IContextManage();

public:
    static void registerConfiguration(QString group, const QJsonObject& obj);

    static void setSystemConfig(const QString& path, const QJsonValue& value);
    static void setApplicationConfig(const QString& path, const QJsonValue& value);
    static void setConfig(const QJsonValue& value, const QString& group, const QString& path = "");

    static QJsonValue getSystemConfig(const QString& path, bool*ok);
    static QJsonValue getApplicationConfig(const QString& path, bool*ok);
    static QJsonValue getConfig(const QString& path, bool* ok, const QString& group);

    static bool getConfigAsBool(const QString& path, bool* ok=nullptr, const QString& group=ApplicationConfigurationGroup);
    static int getConfigAsInt(const QString& path, bool* ok=nullptr, const QString& group=ApplicationConfigurationGroup);
    static double getConfigAsDouble(const QString& path, bool* ok=nullptr, const QString& group=ApplicationConfigurationGroup);
    static QString getConfigAsString(const QString& path, bool* ok=nullptr, const QString& group=ApplicationConfigurationGroup);

public:
    template<typename T>
    static T getBean(const QString& path, bool*ok, const QString& group = ApplicationConfigurationGroup);
    static void getConfigBean(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaProperty>&props, bool*ok);

private:
    friend class ITaskManage;
    QMap<QString, QJsonObject> m_configs;
};

template<typename T>
T IContextManage::getBean(const QString &path, bool* ok, const QString &group)
{
    auto value = getConfig(path, ok, group);
    auto bean = T::fromJson(value.toObject());
    return bean;
}

$PackageWebCoreEnd
