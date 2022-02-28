#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

extern const char FatalType[];
extern const char WarningType[];

struct IAssertInfo {
    QString key;
    QString description;
    QString reason;
    QString solution;
};

// TODO: 预备上， 提供更多有用的调试信息
struct IAssertDetail{
    QString functionName;
    QStringList infos;
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
    static void warn(const QString& name, const QString& extra = "");

private:
    QMap<QString, IAssertInfo> m_fatalInfos;
    QMap<QString, IAssertInfo> m_warnInfos;
};

$PackageWebCoreEnd
