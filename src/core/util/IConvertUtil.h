#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/base/IResult.h"

$PackageWebCoreBegin

namespace  IConvertUtil
{
    QDate toDate(const QString& val, bool& ok);
    QTime toTime(const QString& val, bool& ok);
    QDateTime toDateTime(const QString& val, bool& ok);
    QString toUtcString(const QDateTime& dateTime);
}

$PackageWebCoreEnd
