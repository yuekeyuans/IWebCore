#pragma once
#include "core/base/IHeaderUtil.h"
#include "IJsonUtil_tojson.h"

$PackageWebCoreBegin
namespace IJsonUtil
{
    QVariant getJsonVariantValue(const QJsonObject&obj, const QString& type, const QString path, bool* ok);
    QJsonValue getJsonValue(const QJsonValue& obj, const QString& path, bool* ok=nullptr);

    //! @note 当编写 文档时，注意 jsonvalue 的转换规则
    QJsonValue toJsonValue(const QString& content, bool* ok);
    QJsonValue toJsonValue(const QByteArray& value, bool* ok);
    QJsonValue toJsonValue(bool content, bool* ok);
    QJsonValue toJsonValue(qint64 content, bool* ok);
    QJsonValue toJsonValue(int content, bool* ok);
    QJsonValue toJsonValue(double content, bool* ok);
    QJsonValue toJsonValue(const QJsonValue& value, bool* ok);
    QJsonValue toJsonValue(const QMap<QString, QVariant>& map, bool*ok = nullptr);
    QJsonValue toJsonValue(const QHash<QString, QVariant>& hash, bool* ok=nullptr);
    QJsonValue toJsonValue(const QList<QMap<QString, QVariant>>& list, bool* ok=nullptr); // 按照道理来说，这个是多余的，但是写上，其他地方用到了
    QJsonValue toJsonValue(const QStringList& list, bool* ok=nullptr);
    QJsonValue toJsonValue(const QList<QVariant>& list, bool* ok=nullptr);
    QJsonValue toJsonValue(const QVariant& value, bool *ok=nullptr);

    QJsonArray toJsonArray(const QString& value, bool *ok=nullptr);
    QJsonArray toJsonArray(const QByteArray& value, bool *ok=nullptr);
    QJsonArray toJsonArray(const QJsonValue& value, bool *ok=nullptr);
    QJsonObject toJsonObject(const QString& value, bool *ok=nullptr);
    QJsonObject toJsonObject(const QByteArray& value, bool *ok=nullptr);
    QJsonObject toJsonObject(const QJsonValue& value, bool *ok=nullptr);
    QJsonObject toJsonObject(const QMap<QString, QVariant>&map, bool*ok = nullptr);

    QJsonArray toJsonObjectArray(const QList<QMap<QString, QVariant>>&list, bool* ok=nullptr);

    QString toString(const QJsonObject &json);
    QString toString(const QJsonArray &json);
    QString toString(const QJsonValue &json);

    QByteArray toByteArray(const QJsonObject &json, bool* ok=nullptr);
    QByteArray toByteArray(const QJsonArray &json, bool* ok=nullptr);
    QByteArray toByteArray(const QJsonValue &json, bool* ok=nullptr);

    QString objectToString(const QJsonValue& value);
    QString objectToString(const QJsonArray& value);
    QString objectToString(const QJsonObject& value);

    QVariant toVariant(const QJsonValue& value, QMetaType::Type type, bool* ok=nullptr);

    template<class T>
    QString toString(T value){
        QJsonValue val = IJsonUtil::_objectToJson(value);
        return toString(val);
    }

    template<class T>
    QJsonValue toJsonValue(T value){
        return IJsonUtil::_objectToJson(value);
    }
}

namespace IConvertUtil {
    using IJsonUtil::toJsonValue;
    using IJsonUtil::toJsonArray;
    using IJsonUtil::toJsonObject;
    using IJsonUtil::toJsonObjectArray;
    using IJsonUtil::toByteArray;
    using IJsonUtil::toString;
    using IJsonUtil::objectToString;
//    using IJsonUtil::objectToJson;
    using IJsonUtil::toVariant;
}

$PackageWebCoreEnd
