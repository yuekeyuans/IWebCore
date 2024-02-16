#include "IJsonUtil.h"
#include "IToeUtil.h"
#include "IConvertUtil.h"
#include "IConstantUtil.h"

$PackageWebCoreBegin

QVariant IJsonUtil::getJsonVariantValue(const QJsonObject &obj, const QString &type, const QString path, bool *ok)
{
    IToeUtil::setOk(ok, true);
    bool convertOk;
    auto value = getJsonValue(obj, path, &convertOk);
    IToeUtil::setOkAnd(ok, convertOk);

    if(!convertOk){
        return {};
    }

    if(type == "QString"){
        return value.toString();
    } else if(type == "int"){
        return value.toInt();
    } else if(type == "bool"){
        return value.toBool();
    } else if(type == "double"){
        return value.toDouble();
    }
    IToeUtil::setOk(ok, false);
    return {};
}

QJsonValue IJsonUtil::getJsonValue(const QJsonValue &obj, const QString &path, bool *ok)
{
    IToeUtil::setOk(ok, true);
    QStringList args = path.split(".");
    QJsonValue value = obj;
    int arrayIndex {0};
    for(auto it = args.begin(); it != args.end(); it++){
        bool isArrayIndex = it->startsWith("_");
        if(isArrayIndex){
            bool convertOk;
            arrayIndex = it->midRef(1).toUInt(&convertOk);
            IToeUtil::setOkAnd(ok, convertOk);
            if(!convertOk){
                return {};
            }
        }

        if(value.isUndefined() || value.isNull()){
            IToeUtil::setOk(ok, false);
            return {};
        }

        if(value.isObject() && !isArrayIndex){
            value = value.toObject().value(*it);
        }else if(value.isArray() && isArrayIndex && value.toArray().size() > arrayIndex){
            value = value.toArray()[arrayIndex];
        }else {
            IToeUtil::setOk(ok, false);
            return {};
        }
    }
    // check
    if(value.isUndefined() || value.isNull()){
        IToeUtil::setOk(ok, false);
        return {};
    }

    return value;
}

QJsonValue IJsonUtil::toJsonValue(const QString& content, bool *ok)
{
    if(content.trimmed().isEmpty()){
        IToeUtil::setOk(ok, false);
        return {};
    }

    IToeUtil::setOk(ok, true);
    QJsonParseError error;
    QJsonDocument obj = QJsonDocument::fromJson(content.toUtf8(), &error);
    if(error.error == QJsonParseError::NoError){
        if(obj.isArray()){
            return obj.array();
        }else if(obj.isObject()){
            return obj.object();
        }else if(obj.isEmpty()){
            return QJsonValue();  // null 转化为 空值
        }else if(obj.isNull()){
            IToeUtil::setOk(ok, false);
            return {};
        }
    }
    // 其他类型统一转换成 QString的值
    qDebug() << "convert json failed, error: " << error.errorString();
//    IToeUtil::setOk(ok, false);
    return QJsonValue(content);
}

QJsonValue IJsonUtil::toJsonValue(const QByteArray &value, bool *ok)
{
    return toJsonValue(QString(value), ok);
}


QJsonValue IJsonUtil::toJsonValue(bool content, bool *ok)
{
    IToeUtil::setOk(ok, true);
    return QJsonValue(content);
}


QJsonValue IJsonUtil::toJsonValue(qint64 content, bool *ok)
{
    IToeUtil::setOk(ok, true);
    return QJsonValue(content);
}

QJsonValue IJsonUtil::toJsonValue(int content, bool *ok)
{
    IToeUtil::setOk(ok, true);
    return QJsonValue(content);
}

QJsonValue IJsonUtil::toJsonValue(double content, bool *ok)
{
    IToeUtil::setOk(ok, true);
    return QJsonValue(content);
}

QJsonValue IJsonUtil::toJsonValue(const QJsonValue &value, bool *ok)
{
    IToeUtil::setOk(ok, true);
    return value;
}


QJsonValue IJsonUtil::toJsonValue(const QHash<QString, QVariant> &hash, bool *ok)
{
    IToeUtil::setOk(ok, true);
    const auto keys = hash.keys();
    QJsonObject obj;
    bool convertOk;
    for(const auto& key : keys){
        obj[key] = toJsonValue(hash[key], &convertOk);
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return obj;
}

QJsonValue IJsonUtil::toJsonValue(const QList<QMap<QString, QVariant> > &list, bool *ok)
{
    IToeUtil::setOk(ok, true);
    QJsonArray array;
    bool convertOk;
    for(const auto& map : list){
        array.append(toJsonValue(map, &convertOk));
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return array;
}

QJsonValue IJsonUtil::toJsonValue(const QStringList &list, bool *ok)
{
    IToeUtil::setOk(ok, true);
    QJsonArray array;
    for(const auto& val : list){
        array.append(val);
    }
    return  array;
}

QJsonValue IJsonUtil::toJsonValue(const QList<QVariant> &list, bool *ok)
{
    IToeUtil::setOk(ok, true);
    QJsonArray array;
    bool convertOk;
    for(const auto& val : list){
        array.append(toJsonValue(val, &convertOk));
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return array;
}

// NOTE: 当涉及 uchar ushort 等类型的时候, QVariant::Type 已经不能满足需要了，所以，这里需要有一点特别的处理
QJsonValue IJsonUtil::toJsonValue(const QVariant &value, bool *ok)
{
    IToeUtil::setOk(ok, true);
    auto type = QMetaType::Type(value.type());
    switch (type) {
    case QMetaType::UnknownType:
        IToeUtil::setOk(ok, false);
        return {};
    case QMetaType::Bool:
        return value.toBool();
    case QMetaType::Char:
    case QMetaType::UChar:
        return value.toInt();
    case QMetaType::Short:
    case QMetaType::UShort:
    case QMetaType::Int:
    case QMetaType::UInt:
    case QMetaType::Long:
    case QMetaType::ULong:
    case QMetaType::LongLong:
        return value.toLongLong();
    case QMetaType::ULongLong:
    case QMetaType::Double:
    case QMetaType::Float:
        return value.toDouble();

    case QMetaType::QString:
        return value.toString();
    case QMetaType::QDate:
        return value.toDate().toString(IConstantUtil::DateFormat);
    case QMetaType::QDateTime:
        return value.toDateTime().toString(IConstantUtil::DateTimeFormat);
    case QMetaType::QTime:
        return value.toTime().toString(IConstantUtil::TimeFormat);
    case QMetaType::QVariantMap:
        return toJsonValue(value.toMap());
    case QMetaType::QVariantList:
        return toJsonValue(value.toList());
    case QMetaType::QStringList:
        return toJsonValue(value.toStringList());
    case QMetaType::QByteArray:           //! @note try convert
        return QString(value.toByteArray());
    case QMetaType::QVariantHash:
        return toJsonValue(value.toHash());
    default:
        qFatal("can not convert this type, please check your code");
    }
    return {};
}

QString IJsonUtil::toString(const QJsonValue &json)
{
    if(json.isObject()){
        return toString(json.toObject());
    }else if(json.isArray()){
        return toString(json.toArray());
    }else{
        return json.toString();
    }
}

QJsonValue IJsonUtil::toJsonValue(const QMap<QString, QVariant> &map, bool *ok)
{
    IToeUtil::setOk(ok, true);
    QJsonObject obj;
    const auto& keys = map.keys();
    bool convertOk;
    for(const auto& key : keys){
        obj[key] = IConvertUtil::toJsonValue(map[key], &convertOk);
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return obj;
}

QJsonArray IJsonUtil::toJsonArray(const QString &value, bool *ok)
{
    IToeUtil::setOk(ok, true);
    bool convertOk;
    auto val = IJsonUtil::toJsonValue(value, &convertOk);
    IToeUtil::setOkAnd(ok, convertOk);

    if(!convertOk){
        return {};
    }
    return toJsonArray(val, ok);
}

QJsonArray IJsonUtil::toJsonArray(const QJsonValue &value, bool *ok)
{
    IToeUtil::setOk(ok, true);
    if(!value.isArray()){
        IToeUtil::setOk(ok, false);
        return {};
    }
    return value.toArray();
}

QJsonArray IJsonUtil::toJsonArray(const QByteArray &value, bool *ok)
{
    return toJsonArray(QString(value), ok);
}

QJsonObject IJsonUtil::toJsonObject(const QString &value, bool *ok)
{
    IToeUtil::setOk(ok, true);
    bool convertOk;
    auto val = IJsonUtil::toJsonValue(value, &convertOk);
    IToeUtil::setOkAnd(ok, convertOk);

    if(!convertOk){
        return {};
    }
    return toJsonObject(val, ok);
}

QJsonObject IJsonUtil::toJsonObject(const QJsonValue &value, bool *ok)
{
    IToeUtil::setOk(ok, true);
    if(!value.isObject()){
        IToeUtil::setOk(ok, false);
        return {};
    }
    return value.toObject();
}

QJsonObject IJsonUtil::toJsonObject(const QMap<QString, QVariant> &map, bool* ok)
{
    return IConvertUtil::toJsonObject(IConvertUtil::toJsonValue(map, ok));
}

QJsonObject IJsonUtil::toJsonObject(const QByteArray &value, bool *ok)
{
    return toJsonObject(QString(value), ok);
}

QJsonArray IJsonUtil::toJsonObjectArray(const QList<QMap<QString, QVariant>> &list, bool *ok)
{
    return IConvertUtil::toJsonArray(IConvertUtil::toJsonValue(list, ok));
}

QString IJsonUtil::toString(const QJsonArray &json)
{
    return QString(QJsonDocument(json).toJson(QJsonDocument::Compact));
}

QString IJsonUtil::toString(const QJsonObject &json)
{
    return QString(QJsonDocument(json).toJson(QJsonDocument::Compact));
}

QByteArray IJsonUtil::toByteArray(const QJsonObject &json, bool*ok)
{
    IToeUtil::setOk(ok, true);
    return QJsonDocument(json).toJson(QJsonDocument::Compact);
}

QByteArray IJsonUtil::toByteArray(const QJsonArray &json, bool*ok)
{
    IToeUtil::setOk(ok, true);
    return QJsonDocument(json).toJson(QJsonDocument::Compact);
}

QByteArray IJsonUtil::toByteArray(const QJsonValue &json, bool* ok)
{
    IToeUtil::setOk(ok, true);
    if(json.isObject()){
        return toByteArray(json.toObject());
    }else if(json.isArray()){
        return toByteArray(json.toArray());
    }else if(json.isString()){
        return json.toString().toUtf8();
    }else if(json.isBool()){
        return QString(json.toBool()).toUtf8();
    }else if(json.isDouble()){
        return QString::number(json.toDouble()).toUtf8();
    }else if(json.isUndefined() || json.isNull()){
        IToeUtil::setOk(ok, false);
        return {};
    }
    return {};
}

QString IJsonUtil::objectToString(const QJsonValue &value)
{
    return toString(value);
}

QString IJsonUtil::objectToString(const QJsonArray &value)
{
    return toString(value);
}

QString IJsonUtil::objectToString(const QJsonObject &value)
{
    return toString(value);
}


//! @note not safe!
QVariant IJsonUtil::toVariant(const QJsonValue &value, QMetaType::Type type, bool *ok)
{
    static const QList<QMetaType::Type> validTypes = {
        QMetaType::Bool,
        QMetaType::QString,
        QMetaType::QByteArray,
        QMetaType::QStringList, // support QStringList.
        QMetaType::Short, QMetaType::UShort,
        QMetaType::Int, QMetaType::UInt,
        QMetaType::Long, QMetaType::ULong,
        QMetaType::LongLong, QMetaType::ULongLong,
        QMetaType::Double, QMetaType::Float,
        QMetaType::QDate, QMetaType::QTime, QMetaType::QDateTime,   // support time
    };
    IToeUtil::setOk(ok, true);
    if(!validTypes.contains(type)){
        IToeUtil::setOk(ok, false);
        return {};
    }

    switch (type) {
    case QMetaType::UnknownType:
        IToeUtil::setOk(ok, false);
        return {};
    case QMetaType::Bool:
        return value.toBool();
    case QMetaType::Short:
    case QMetaType::UShort:
    case QMetaType::Int:
    case QMetaType::UInt:
        return value.toInt();
    case QMetaType::Long:
    case QMetaType::ULong:
    case QMetaType::LongLong:
        return value.toDouble();
    case QMetaType::ULongLong:
    case QMetaType::Double:
    case QMetaType::Float:
        return value.toDouble();
    case QMetaType::QString:
        return value.toString();
    case QMetaType::QDate:
        return QVariant(value.toString()).toDate();
    case QMetaType::QDateTime:
        return QVariant(value.toString()).toDateTime();
    case QMetaType::QTime:
        return QVariant(value.toString()).toTime();
    case QMetaType::QStringList:{
        bool convertOk;
        auto list = IJsonUtil::toJsonArray(value, &convertOk);
        IToeUtil::setOk(ok, convertOk);
        if(!convertOk){
            return {};
        }
        QStringList ret;
        for(const auto& val : list){
            ret.append(val.toString());
        }
        return ret;
    }
    case QMetaType::QByteArray:           //! @note try convert
        return value.toString().toUtf8();
    default:
        qFatal("can not convert this type, please check your code");
    }
    return {};
}

static bool isJsonIndex(const QString& arg)
{
    if(!arg.startsWith("_")){
        return false;
    }

    bool ok{false};
    arg.mid(1).toInt(&ok);
    return ok;
}

static int getJsonIndex(const QString& arg)
{
    return arg.mid(1).toInt();
}

void IJsonUtil::addToJsonObject(QJsonObject &obj, const QString &path, QJsonValue value)
{
    QStringList args = path.split(".");
    assert(args.length() != 0);
    assert(!isJsonIndex(args.first()));

}

QJsonValue IJsonUtil::getJsonValue(const QJsonObject &obj, const QString &path, bool *ok)
{
    return {};
}


$PackageWebCoreEnd
