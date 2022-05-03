#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IDebugInterface
{
public:
    struct Info{
        QString tag;
        QString reason;
        QString solution;
    };

    enum Level{
        Debug,
        Warn,
        Error,
        Fatal
    };

public:
    IDebugInterface() = default;

    void debug(const QString& tag, const QStringList& extra={});
    void warn(const QString& tag, const QStringList& extra={});
    void error(const QString& tag, const QStringList& extra={});
    void fatal(const QString& tag, const QStringList& extra={});

protected:
    virtual QJsonObject jsonFormatedInfo() = 0;
    void loadConfigs();

private:
    QList<Info> m_debugInfos;
    QList<Info> m_warnInfos;
    QList<Info> m_errorInfos;
    QList<Info> m_fatalInfos;
};

$PackageWebCoreEnd
