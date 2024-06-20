#pragma once
#include "core/base/IHeaderUtil.h"
#include "core/base/IJsonUtil_tojson.h"

$PackageWebCoreBegin
namespace IJsonUtil
{
    QJsonValue getJsonValue(const QJsonValue& obj, const QString& path, bool& ok);

    //! @note 当编写 文档时，注意 jsonvalue 的转换规则
    QJsonValue toJsonValue(const QString& content, bool& ok);
    QJsonValue toJsonValue(const QByteArray& value, bool& ok);
    QJsonValue toJsonValue(IStringView value, bool& ok);
    IResult<QJsonValue> toJsonValue(IStringView value);

    QJsonValue toJsonValue(bool content, bool& ok);
    QJsonValue toJsonValue(qint64 content, bool& ok);
    QJsonValue toJsonValue(int content, bool& ok);
    QJsonValue toJsonValue(double content, bool& ok);
    QJsonValue toJsonValue(const QJsonValue& value, bool& ok);
    QJsonValue toJsonValue(const QMap<QString, QVariant>& map, bool& ok);
    QJsonValue toJsonValue(const QHash<QString, QVariant>& hash, bool& ok);
    QJsonValue toJsonValue(const QList<QMap<QString, QVariant>>& list, bool& ok); // 按照道理来说，这个是多余的，但是写上，其他地方用到了
    QJsonValue toJsonValue(const QStringList& list, bool& ok);
    QJsonValue toJsonValue(const QList<QVariant>& list, bool& ok);
    QJsonValue toJsonValue(const QVariant& value, bool& ok);


    template<typename T>
    QJsonValue toJsonValue(T value, bool& ok){
        return IJsonUtil::_objectToJson(value, ok);
    }

    template<typename T>
    IResult<QJsonValue> toJsonValue(T value){
        bool ok;
        auto val = toJsonValue<T>(value, ok);
        return {val, ok};
    }

    QJsonArray toJsonArray(const QStringList& value, bool& ok);
    QJsonArray toJsonArray(const QString& value, bool& ok);
    QJsonArray toJsonArray(const QByteArray& value, bool& ok);
    QJsonArray toJsonArray(const QJsonValue& value, bool& ok);
    QJsonObject toJsonObject(const QString& value, bool& ok);
    IResult<QJsonObject> toJsonObject(const QString& value);

    QJsonObject toJsonObject(const QByteArray& value, bool& ok);
    QJsonObject toJsonObject(const QJsonValue& value, bool& ok);
    QJsonObject toJsonObject(const QMap<QString, QVariant>&map, bool& ok);

    QJsonArray toJsonObjectArray(const QList<QMap<QString, QVariant>>&list, bool& ok);

    QByteArray toByteArray(const QJsonObject &json, bool& ok);
    QByteArray toByteArray(const QJsonArray &json, bool& ok);
    QByteArray toByteArray(const QJsonValue &json, bool& ok);

    QString objectToString(const QJsonValue& value);
    QString objectToString(const QJsonArray& value);
    QString objectToString(const QJsonObject& value);

    QVariant toVariant(const QJsonValue& value, QMetaType::Type type, bool& ok);

    QString toString(QJsonValue value);

    // TODO: 看一下这个怎搞？, 这个应该可以不要的。
    template<class T>
    QString toString(T value){
        bool ok;
        QJsonValue val = IJsonUtil::_objectToJson(value, ok);
        if(!ok){
            return {};
        }
        return toString(val);
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
    using IJsonUtil::toVariant;
}


$PackageWebCoreEnd

#include "core/base/IJsonUtil_fromjson.h"
