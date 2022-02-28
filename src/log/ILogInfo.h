#pragma once

#include "base/IHeaderUtil.h"


$PackageWebCoreBegin

struct ILogInfo
{
    int lineNumber;
    QString fileName;
    QString functionName;

    QString message;
    QMap<QString, QString> extras;
    QDateTime time;

public:
    virtual void log();
    virtual ILogInfo& setExtra(const QString& key, const QString& value);
    virtual ILogInfo& setMessage(const QString& message);
};

$PackageWebCoreEnd
