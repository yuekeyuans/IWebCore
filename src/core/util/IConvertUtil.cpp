#include "IConvertUtil.h"
#include "IToeUtil.h"
#include "IConstantUtil.h"

$PackageWebCoreBegin

QDate IConvertUtil::toDate(const QString &val, bool& ok)
{
    QVariant variant = val;
    auto date = variant.toDate();
    IToeUtil::setOk(ok, date.isValid());
    return date;
}

QTime IConvertUtil::toTime(const QString &val, bool& ok)
{
    QVariant variant = val;
    auto time = variant.toTime();
    IToeUtil::setOk(ok, time.isValid());
    return time;
}

QDateTime IConvertUtil::toDateTime(const QString &val, bool& ok)
{
    QVariant variant = val;
    auto dateTime = variant.toDateTime();
    IToeUtil::setOk(ok, dateTime.isValid());
    return dateTime;
}

QString IConvertUtil::toUtcString(const QDateTime& dateTime)
{
    static const QString format = "ddd, dd MMM yyyy hh:mm:ss";
    static const QLocale local = QLocale::English;
    auto str = local.toString(dateTime.toUTC(), format).append(" GMT");
    return str;
}

$PackageWebCoreEnd
