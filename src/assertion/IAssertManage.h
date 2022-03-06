#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IAssertDetail;
extern const char FatalType[];
extern const char WarningType[];

struct IAssertInfo {
    QString key;
    QString description;
    QString reason;
    QString solution;
};

class IAssertManage
{
    $UseInstance(IAssertManage)
private:
    IAssertManage();

public:
    static void registerFatalInfo(const IAssertInfo& info);
    static void registerWarnInfo(const IAssertInfo& info);

    static void fatal(const QString& name, const QString& extra = "");
    static void fatal(const QString& name, const IAssertDetail& detail);

    static void warn(const QString& name, const QString& extra = "");
    static void warn(const QString& name, const IAssertDetail& detail);

private:
    QMap<QString, IAssertInfo> m_fatalInfos;
    QMap<QString, IAssertInfo> m_warnInfos;
};

$PackageWebCoreEnd
