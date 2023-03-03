#include "IConvertUtil.h"
#include "IToeUtil.h"
#include "IConstantUtil.h"
#include "IJsonUtil.h"

$PackageWebCoreBegin

namespace IConvertUtilHelper{
    QVariant toLong(long value);
    QVariant toULong(ulong value);
}

bool IConvertUtil::toBool(bool value, bool *ok)
{
    IToeUtil::setOk(ok, true);
    if(value){
        return true;
    }
    return false;
}

/*!
 * convert QString type to bool. the QString will be passed to IToeUtil::isTruthy function
 * is the QString value is truthy, the function will return true, else false.
 *
 * \param vaue string that to be converted to bool
 * \param[out] ok if convertion fails ok will be set to false
 * \return
 */
bool IConvertUtil::toBool(const QString &value, bool *ok)
{
    IToeUtil::setOk(ok, true);
    return IToeUtil::isTruthy(value);
}

bool IConvertUtil::toBool(const QJsonValue &value, bool *ok)
{
    if(value.isArray() || value.isObject() || value.isNull() || value.isUndefined()){
        IToeUtil::setOk(ok, false);
        return false;
    }

    IToeUtil::setOk(ok, true);
    if(value.isBool()){
        return value.toBool();
    }else if(value.isDouble()){
        return value.toInt() != 0;
    }else if(value.isString()){
        return toBool(value.toString(), ok);
    }
    // unreachable
    IToeUtil::setOk(ok, false);
    return false;
}

short IConvertUtil::toShort(const QString &value, bool *ok, int base)
{
    return std::mem_fn(&QString::toShort)(value, ok, base);
}

short IConvertUtil::toShort(const QJsonValue &value, bool *ok)
{
    int val = toInt(value, ok);
    if(ok && val >= std::numeric_limits<short>::min() && val <= std::numeric_limits<short>::max()){
        return static_cast<short>(val);
    }

    IToeUtil::setOk(ok, false);
    return {};
}

ushort IConvertUtil::toUShort(const QString &value, bool *ok, int base)
{
    return std::mem_fn(&QString::toUShort)(value, ok, base);
}

ushort IConvertUtil::toUShort(const QJsonValue &value, bool *ok)
{
    uint val = toUInt(value, ok);
    if(ok && val >= std::numeric_limits<ushort>::min() && val <= std::numeric_limits<ushort>::max()){
        return static_cast<ushort>(val);
    }
    IToeUtil::setOk(ok, false);
    return {};
}

int IConvertUtil::toInt(const QString &value, bool *ok, int base)
{
    return std::mem_fn(&QString::toInt)(value, ok, base);
}

int IConvertUtil::toInt(const QJsonValue &value, bool *ok)
{
    if(value.isArray() || value.isObject() || value.isNull() || value.isUndefined() || value.isBool()){
        IToeUtil::setOk(ok, false);
        return 0;
    }

    IToeUtil::setOk(ok, true);
    if(value.isDouble()){
        return value.toInt();
    }else if(value.isString()){
        return toInt(value.toString(), ok);
    }
    IToeUtil::setOk(ok, false);
    return 0;
}

uint IConvertUtil::toUInt(const QString &value, bool *ok, int base)
{
    return std::mem_fn(&QString::toUInt)(value, ok, base);
}

uint IConvertUtil::toUInt(const QJsonValue &value, bool *ok)
{
    if(value.isArray() || value.isObject() || value.isNull() || value.isUndefined() || value.isBool()){
        IToeUtil::setOk(ok, false);
        return 0;
    }

    IToeUtil::setOk(ok, true);
    if(value.isDouble()){
        return toUInt(value.toString(), ok);
    }else if(value.isString()){
        return toInt(value.toString(), ok);
    }
    IToeUtil::setOk(ok, false);
    return {};
}

long IConvertUtil::toLong(const QString &value, bool *ok, int base)
{
    return std::mem_fn(&QString::toLong)(value, ok, base);
}

ulong IConvertUtil::toULong(const QString &value, bool *ok, int base)
{
    return std::mem_fn(&QString::toULong)(value, ok, base);
}

qlonglong IConvertUtil::toLongLong(const QString &value, bool *ok, int base)
{
    return std::mem_fn(&QString::toLongLong)(value, ok, base);
}

qulonglong IConvertUtil::toULongLong(const QString &value, bool *ok, int base)
{
    return std::mem_fn(&QString::toULongLong)(value, ok, base);
}

float IConvertUtil::toFloat(const QString &value, bool *ok)
{
    return std::mem_fn(&QString::toFloat)(value, ok);
}

double IConvertUtil::toDouble(const QString &value, bool *ok)
{
    return std::mem_fn(&QString::toDouble)(value, ok);
}


double IConvertUtil::toDouble(const QJsonValue &value, bool *ok)
{
    if(value.isArray() || value.isObject() || value.isNull() || value.isUndefined() || value.isBool()){
        IToeUtil::setOk(ok, false);
        return 0;
    }

    IToeUtil::setOk(ok, true);
    if(value.isDouble()){
        return value.toDouble();
    }else if(value.isString()){
        return toDouble(value.toString(), ok);
    }
    IToeUtil::setOk(ok, false);
    return 0;
}

QString IConvertUtil::toString(bool value)
{
    return value ? "true" : "false";
}

// 保留10 位有效精度
QString IConvertUtil::toString(double value, char format, int precision)
{
    return QString::number(value, format, precision);
}

QString IConvertUtil::toString(int value)
{
    return QString::number(value);
}

QString IConvertUtil::toString(uint value)
{
    return QString::number(value);
}

QString IConvertUtil::toString(long value)
{
    return QString::number(value);
}

QString IConvertUtil::toString(ulong value)
{
    return QString::number(value);
}

QString IConvertUtil::toString(qlonglong value)
{
    return QString::number(value);
}

QString IConvertUtil::toString(qulonglong value)
{
    return QString::number(value);
}

QString IConvertUtil::toString(const QString &value)
{
    return value;
}

QString IConvertUtil::toString(const QByteArray &value)
{
    return QString::fromUtf8(value);
}

QString IConvertUtil::toString(const QStringList &value)
{
    auto string = value.join("\", \"");
    string = QString("[\"").append(string).append("\"]");
    return string;
}

QString IConvertUtil::toString(const QMap<QString, QVariant> &value)
{
    return IJsonUtil::toString(IJsonUtil::toJsonValue(value));
}

QByteArray IConvertUtil::toByteArray(const QString &value)
{
    return value.toUtf8();
}

QByteArray IConvertUtil::toByteArray(const QByteArray &value)
{
    return value;
}

QString IConvertUtil::toString(const QDate &date)
{
    return date.toString(IConstantUtil::DateFormat);
}

QString IConvertUtil::toString(const QDateTime &datetime)
{
    return datetime.toString(IConstantUtil::DateTimeFormat);
}

QString IConvertUtil::toString(const QTime &time)
{
    return time.toString(IConstantUtil::TimeFormat);
}

//QString IConvertUtil::toString(const QJsonArray &json)
//{
//    return QString(QJsonDocument(json).toJson(QJsonDocument::Compact));
//}

//QString IConvertUtil::toString(const QJsonObject &json)
//{
//    return QString(QJsonDocument(json).toJson(QJsonDocument::Compact));
//}

//QString IConvertUtil::toString(const QJsonValue &json)
//{
//    if(json.isObject()){
//        return toString(json.toObject());
//    }else if(json.isArray()){
//        return toString(json.toArray());
//    }else{
//        return json.toString();
//    }
//}

QDate IConvertUtil::toDate(const QString &val, bool* ok)
{
    QVariant variant = val;
    auto date = variant.toDate();
    IToeUtil::setOk(ok, date.isValid());
    return date;
}

QTime IConvertUtil::toTime(const QString &val, bool* ok)
{
    QVariant variant = val;
    auto time = variant.toTime();
    IToeUtil::setOk(ok, time.isValid());
    return time;
}

QDateTime IConvertUtil::toDateTime(const QString &val, bool* ok)
{
    QVariant variant = val;
    auto dateTime = variant.toDateTime();
    IToeUtil::setOk(ok, dateTime.isValid());
    return dateTime;
}


QList<QVariant> IConvertUtil::toList(const QVariant &value, bool *ok)
{
    if(value.type() == QVariant::List){
        IToeUtil::setOkAnd(ok, true);
        return value.toList();
    }
    IToeUtil::setOk(ok, false);
    return {};
}

QMap<QString, QVariant> IConvertUtil::toMap(const QVariant &value, bool *ok)
{
    if(value.type() == QVariant::Map){
        IToeUtil::setOkAnd(ok, true);
        return value.toMap();
    }
    IToeUtil::setOk(ok, false);
    return {};
}

QVariant IConvertUtil::toVariant(const QJsonValue &value, bool *ok)
{
    IToeUtil::setOk(ok, true);
    switch (value.type()) {
    case QJsonValue::Bool:
        return value.toBool();
    case QJsonValue::Null:
        IToeUtil::setOk(ok, false);
        return {};
    case QJsonValue::Undefined:
        IToeUtil::setOk(ok, false);
        return {};
    case QJsonValue::Double:
        return value.toDouble();
    case QJsonValue::String:
        return value.toString();
    case QJsonValue::Array:
        return toVariant(value.toArray());
    case QJsonValue::Object:
        return toVariant(value.toObject());
    }
    IToeUtil::setOk(ok, false);
    return {};
}

QVariant IConvertUtil::toVariant(const QJsonArray &array, bool *ok)
{
    IToeUtil::setOk(ok, true);
    QList<QVariant> ret;
    for(const QJsonValue& value : array){
        bool convertOk;
        ret.append(toVariant(value, &convertOk));
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return ret;
}

QVariant IConvertUtil::toVariant(const QJsonObject &obj, bool *ok)
{
    IToeUtil::setOk(ok, true);
    QMap<QString, QVariant> ret;
    const auto& keys = obj.keys();
    for(const auto& key : keys){
        bool convertOk;
        ret[key] = toVariant(obj[key], &convertOk);
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return ret;
}

QVariant IConvertUtil::toVariant(const QByteArray &value, QMetaType::Type destType, bool* ok)
{
    return toVariant(QString(value), destType, ok);
}

QVariant IConvertUtil::toVariant(const QString &value, QMetaType::Type destType, bool *ok)
{
    IToeUtil::setOk(ok, true);
    switch (destType) {
    case QMetaType::Bool:
        return IConvertUtil::toBool(value, ok);
    case QMetaType::Short:
        return IConvertUtil::toShort(value, ok);
    case QMetaType::UShort:
        return IConvertUtil::toUShort(value, ok);
    case QMetaType::Int:
        return IConvertUtil::toInt(value, ok);
    case QMetaType::UInt:
        return IConvertUtil::toUInt(value, ok);
    case QMetaType::Long:
        return IConvertUtilHelper::toLong(IConvertUtil::toLong(value, ok));
    case QMetaType::ULong:
        return IConvertUtilHelper::toULong(IConvertUtil::toLong(value, ok));
    case QMetaType::LongLong:
        return IConvertUtil::toLongLong(value, ok);
    case QMetaType::ULongLong:
        return IConvertUtil::toULongLong(value, ok);

    case QMetaType::Float:
        return IConvertUtil::toFloat(value, ok);
    case QMetaType::Double:
        return IConvertUtil::toDouble(value, ok);

    case QMetaType::QString:
        return IConvertUtil::toString(value);
    case QMetaType::QByteArray:
        return IConvertUtil::toByteArray(value);

    case QMetaType::QJsonArray:
        return IConvertUtil::toJsonArray(value, ok);
    case QMetaType::QJsonValue:
        return IConvertUtil::toJsonObject(value, ok);
    case QMetaType::QJsonObject:
        return IConvertUtil::toJsonObject(value, ok);

    case QMetaType::QDate:
        return IConvertUtil::toDate(value, ok);
    case QMetaType::QTime:
        return IConvertUtil::toTime(value, ok);
    case QMetaType::QDateTime:
        return IConvertUtil::toDateTime(value,ok);

    default:
        break;                          // other type is not supported now;
    }
    IToeUtil::setOk(ok, false);
    return {};
}

QVariant IConvertUtilHelper::toLong(long val)
{
    if(sizeof (long) == sizeof(int)){
        return static_cast<int>(val);
    } else{
        return static_cast<qlonglong>(val);
    }
}

QVariant IConvertUtilHelper::toULong(ulong val)
{
    if(sizeof (ulong) == sizeof(int)){
        return static_cast<uint>(val);
    } else{
        return static_cast<qulonglong>(val);
    }
}

QString IConvertUtil::toUtcString(const QDateTime& dateTime)
{
    static const QString format = "ddd, dd MMM yyyy hh:mm:ss";
    static const QLocale local = QLocale::English;
    auto str = local.toString(dateTime.toUTC(), format).append(" GMT");
    return str;
}


$PackageWebCoreEnd
