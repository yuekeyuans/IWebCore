#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/result/IResult.h"

$PackageWebCoreBegin

namespace  IConvertUtil
{
    bool toBool(bool value, bool& ok);
    bool toBool(const QString& vaue, bool& ok);
    bool toBool(const QJsonValue& value, bool& ok);

    short  toShort(const QString& value, bool& ok, int base=10);
    short toShort(const QJsonValue& value, bool& ok);
    short toShort(double value, bool& ok);

    ushort toUShort(const QString& value, bool& ok, int base=10);
    ushort toUShort(const QJsonValue& value, bool& ok);
    ushort toUShort(double value, bool& ok);

    int toInt(const QString& value, bool& ok, int base=10);
    int toInt(const QJsonValue& value, bool& ok);
    int toInt(double value, bool& ok);

    uint toUInt(const QString& value, bool& ok, int base=10);
    uint toUInt(const QJsonValue& value, bool& ok);
    uint toUInt(double value, bool& ok);

    long toLong(const QString& value, bool& ok, int base=10);
    long toLong(double value, bool& ok);
    long toLong(const QJsonValue& value, bool& ok);

    ulong toULong(const QString& value, bool& ok, int base=10);
    ulong toULong(double value, bool& ok);
    ulong toULong(const QJsonValue& value, bool& ok);

    qlonglong toLongLong(const QString& value, bool& ok, int base=10);
    qlonglong toLongLong(double value, bool &ok);
    qlonglong toLongLong(const QJsonValue& value, bool& ok);

    qulonglong toULongLong(const QString& value, bool& ok, int base=10);
    qulonglong toULongLong(double value, bool &ok);
    qulonglong toULongLong(const QJsonValue& value, bool& ok);

    float toFloat(const QString& value, bool &ok);
    float toFloat(double value, bool &ok);
    float toFloat(const QJsonValue& value, bool& ok);

    double toDouble(const QString& value, bool &ok);
    double toDouble(const QJsonValue& value, bool &ok);

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

    QString toString(const QJsonValue& value, bool& ok);
    QString toString(const QJsonObject &json);
    QString toString(const QJsonArray &json);

    QStringList toStringList(const QJsonValue& value, bool& ok);

    QByteArray toByteArray(const QString& value);
    QByteArray toByteArray(const QByteArray& value);
    QByteArray toByteArray(const QJsonValue& value);

    // json -> list,map 转换
    QList<QVariant> toList(const QVariant& value, bool& ok);
    QMap<QString, QVariant> toMap(const QVariant& value, bool& ok);

    QVariant toVariant(const QJsonValue& value, bool& ok);
    QVariant toVariant(const QJsonArray& arrray, bool& ok);
    QVariant toVariant(const QJsonObject& object, bool& ok);
    QVariant toVariant(const QByteArray& value, QMetaType::Type destType, bool& ok);
    QVariant toVariant(const QString& value, QMetaType::Type destType, bool& ok);
    QVariant toVariant(IStringView value, QMetaType::Type destType, bool& ok);
    // date datetime, time
    QDate toDate(const QString& val, bool& ok);
    QTime toTime(const QString& val, bool& ok);
    QDateTime toDateTime(const QString& val, bool& ok);

    QString toUtcString(const QDateTime& dateTime);

    // TODO:  add Functions
//    // intergral without bool
//    template<typename T>
//    std::enable_if_t<(std::is_integral_v<T> && std::is_same_v<T, bool>), T> toIntegral(const QJsonValue& value, bool*ok);

//    // floating pointer
//    template<typename T>
//    std::enable_if<std::is_floating_point_v<T>, T> toFloatingPoint(const QJsonValue& value, bool& ok);

//    // bean
//    template<typename T>
//    T toBean(const QJsonValue& value, bool& ok);
}

$PackageWebCoreEnd
