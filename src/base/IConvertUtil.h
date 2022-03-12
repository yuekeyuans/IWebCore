#pragma once

#include "base/IHeaderUtil.h"
#include "base/IJsonUtil.h"
#include "base/IOrmUtil.h"

$PackageWebCoreBegin

/*!
 * @namespace IConvertUtil
 * @brief Utils for convert one type to another type.
 */
namespace  IConvertUtil
{
    bool toBool(bool value, bool *ok = nullptr);
    bool toBool(const QString& vaue, bool *ok=nullptr);
    bool toBool(const QJsonValue& value, bool *ok=nullptr);

    short  toShort(const QString& value, bool *ok=nullptr, int base=10);
    ushort toUShort(const QString& value, bool *ok=nullptr, int base=10);
    int toInt(const QString& value, bool *ok=nullptr, int base=10);
    int toInt(const QJsonValue& value, bool *ok=nullptr);
    uint toUInt(const QString& value, bool *ok=nullptr, int base=10);
    long toLong(const QString& value, bool *ok=nullptr, int base=10);
    ulong toULong(const QString& value, bool *ok=nullptr, int base=10);
    qlonglong toLongLong(const QString& value, bool *ok=nullptr, int base=10);
    qulonglong toULongLong(const QString& value, bool *ok=nullptr, int base=10);
    float toFloat(const QString& value, bool *ok=nullptr);
    double toDouble(const QString& value, bool *ok=nullptr);
    double toDouble(const QJsonValue& value, bool *ok=nullptr);

    QString toString(bool value);
    QString toString(double value, char format = 'g', int precision = 6);
    QString toString(int value);
    QString toString(uint value);
    QString toString(long value);
    QString toString(ulong value);
    QString toString(qlonglong value);
    QString toString(qulonglong value);
    QString toString(const QString& value);
    QString toString(const QByteArray& value);
    QString toString(const QStringList& value);
    QString toString(const QMap<QString, QVariant>& value);
    QString toString(const QDate& date);
    QString toString(const QDateTime& datetime);
    QString toString(const QTime& time);

    QByteArray toByteArray(const QString& value);
    QByteArray toByteArray(const QByteArray& value);

    // json -> list,map 转换
    QList<QVariant> toList(const QVariant& value, bool*ok = nullptr);
    QMap<QString, QVariant> toMap(const QVariant& value, bool*ok=nullptr);

    QVariant toVariant(const QJsonValue& value, bool*ok=nullptr);
    QVariant toVariant(const QJsonArray& arrray, bool* ok=nullptr);
    QVariant toVariant(const QJsonObject& object, bool* ok=nullptr);
    QVariant toVariant(const QByteArray& value, QMetaType::Type destType, bool* ok=nullptr);
    QVariant toVariant(const QString& value, QMetaType::Type destType, bool* ok=nullptr);

    // date datetime, time
    QDate toDate(const QString& val, bool* ok=nullptr);
    QTime toTime(const QString& val, bool* ok=nullptr);
    QDateTime toDateTime(const QString& val, bool* ok=nullptr);


};

$PackageWebCoreEnd
