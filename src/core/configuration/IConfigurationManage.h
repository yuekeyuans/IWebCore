#pragma once

#include "IConfigurationPreProcessor.h"
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

extern const char SystemConfigurationGroup[];
extern const char ApplicationConfigurationGroup[];
//extern const char UserConfigurationGroup[];

class ITaskManage;

class IConfigurationManage
{
    Q_DISABLE_COPY_MOVE(IConfigurationManage);
    $UseInstance(IConfigurationManage)
private:
    IConfigurationManage() = default;

public:
    static void registerConfiguration(QString group, const QJsonObject& obj);

    static void setSystemValue(const QString& path, const QJsonValue& value);
    static void setApplicationValue(const QString& path, const QJsonValue& value);
    static void setValue(const QString& path, const QJsonValue& value, const QString& group);

    static bool getBoolValue(const QString& path, bool* ok=nullptr, const QString& group=ApplicationConfigurationGroup);
    static int getIntValue(const QString& path, bool* ok=nullptr, const QString& group=ApplicationConfigurationGroup);
    static double getDoubleValue(const QString& path, bool* ok=nullptr, const QString& group=ApplicationConfigurationGroup);
    static QString getStringValue(const QString& path, bool* ok=nullptr, const QString& group=ApplicationConfigurationGroup);

    static QJsonValue getSystemValue(const QString& path, bool*ok);
    static QJsonValue getApplicationValue(const QString& path, bool*ok);
    static QJsonValue getValue(const QString& path, bool* ok, const QString& group);

    template<typename T>
    static T getBean(const QString& path, bool*ok, const QString& group = ApplicationConfigurationGroup);
    static void getConfigBean(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaProperty>&props, bool*ok);

private:
    friend class ITaskManage;
    QMap<QString, QJsonObject> m_configs;
};

template<typename T>
T IConfigurationManage::getBean(const QString &path, bool* ok, const QString &group)
{
    auto value = getValue(path, ok, group);
    auto bean = T::fromJson(value.toObject());
    return bean;
}

$PackageWebCoreEnd
