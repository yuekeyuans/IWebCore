#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class ITaskManage;

class IContextManage
{
    $UseInstance(IContextManage)
private:
    IContextManage();

public:
    static QJsonValue getSystemConfig(const QString& path, bool*ok);
    static QJsonValue getApplicationConfig(const QString& path, bool*ok);

    static bool getSystemConfigAsBool(const QString& path, bool* ok=nullptr);
    static int getSystemConfigAsInt(const QString& path, bool* ok=nullptr);
    static double getSystemConfigAsDouble(const QString& path, bool* ok=nullptr);
    static QString getSystemConfigAsString(const QString& path, bool* ok=nullptr);

    static bool getApplicationConfigAsBool(const QString& path, bool* ok=nullptr);
    static int getApplicationConfigAsInt(const QString& path, bool* ok=nullptr);
    static double getApplicationConfigAsDouble(const QString& path, bool* ok=nullptr);
    static QString getApplicationConfigAsString(const QString& path, bool* ok=nullptr);


//    static bool getConfigAsBool(const QString& path, bool* ok=nullptr, const QString& group=ApplicationConfigurationGroup);
//    static int getConfigAsInt(const QString& path, bool* ok=nullptr, const QString& group=ApplicationConfigurationGroup);
//    static double getConfigAsDouble(const QString& path, bool* ok=nullptr, const QString& group=ApplicationConfigurationGroup);
//    static QString getConfigAsString(const QString& path, bool* ok=nullptr, const QString& group=ApplicationConfigurationGroup);

public:
    static QJsonValue getConfig(const QString& path, bool* ok, const QString& group);
    static void addConfig(const QJsonValue& value, const QString& group, const QString& path="");
    static void removeConfig(const QString& group, const QString& path);

public:
    template<typename T>
    static T getBean(const QString& path, bool*ok);
    static void getConfigBean(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaProperty>&props, bool*ok);

public:
    static constexpr char SystemContextGroup[] = "System";
    static constexpr char ApplicationContextGroup[] = "Application";

private:
    friend class ITaskManage;
    QMap<QString, QJsonObject> m_configs;
};

template<typename T>
T IContextManage::getBean(const QString &path, bool* ok)
{
    auto value = getApplicationConfig(path, ok);
    auto bean = T::fromJson(value.toObject());
    return bean;
}

$PackageWebCoreEnd
