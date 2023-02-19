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

    // TODO: 这里遇到一个问题，就是 config 允不允许在程序全面启动之后再注册任何的数据？ 这个理论上不允许，但有没有后门需要留下，防止用户确实有这个需求？
public:
    static void setSystemConfig(const QJsonValue& value, const QString& path="");
    static void setApplicationConfig(const QJsonValue& value, const QString& path="");
    static void setConfig(const QJsonValue& value, const QString& group, const QString& path = "");

public:
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
