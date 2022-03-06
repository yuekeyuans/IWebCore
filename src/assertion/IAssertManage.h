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

struct IAssertDetail{
    Q_GADGET
public:
    enum Type{
        Class,
        Function,
        Line,
        Parameter,
        ReturnValue,
    };
    Q_ENUM(Type)

    void setDetail(Type type, const QString& info);
    QString& operator [](Type);
    QString toString();

private:
    QMap<Type, QString> m_detailInfo;
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
