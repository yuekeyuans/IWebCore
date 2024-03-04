#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IToeUtil.h"
#include "core/base/IJsonUtil.h"
#include "core/result/IResult.h"

$PackageWebCoreBegin

namespace IJsonUtil
{
template<typename T>
T fromJson(const QJsonValue&, bool& ok);
template<typename T>
IResult<T> fromJson(const QJsonValue&);

template<>
int fromJson<int>(const QJsonValue&, bool& ok);
template<>
IResult<int> fromJson<int>(const QJsonValue&);

template<>
ushort fromJson<ushort>(const QJsonValue&, bool& ok);
template<>
IResult<ushort> fromJson<ushort>(const QJsonValue&);

template<>
bool fromJson<bool>(const QJsonValue&, bool& ok);
template<>
IResult<bool> fromJson<bool>(const QJsonValue&);

template<>
QString fromJson<QString>(const QJsonValue&, bool& ok);
template<>
IResult<QString> fromJson<QString>(const QJsonValue&);

template<>
QStringList fromJson<QStringList>(const QJsonValue&, bool& ok);
template<>
IResult<QStringList> fromJson<QStringList>(const QJsonValue&);

template<>
QJsonObject fromJson<QJsonObject>(const QJsonValue&, bool& ok);
template<>
IResult<QJsonObject> fromJson<QJsonObject>(const QJsonValue&);

template<>
QJsonArray fromJson<QJsonArray>(const QJsonValue&, bool& ok);
template<>
IResult<QJsonArray> fromJson<QJsonArray>(const QJsonValue&);

template<>
QJsonValue fromJson<QJsonValue>(const QJsonValue&, bool& ok);
template<>
IResult<QJsonValue> fromJson<QJsonValue>(const QJsonValue&);
}

// TODO: directly copy, this should be changed;
#include "core/base/IConvertUtil.h"

template<>
inline int IJsonUtil::fromJson<int>(const QJsonValue& value, bool& ok){
    return IConvertUtil::toInt(value, ok);
}

template<>
inline IResult<int> IJsonUtil::fromJson<int>(const QJsonValue& value){
    bool ok;
    auto val = IConvertUtil::toInt(value, ok);
    return {val, ok};
}

template<>
inline ushort IJsonUtil::fromJson<ushort>(const QJsonValue& value, bool& ok){
    return IConvertUtil::toUShort(value, ok);
}

template<>
inline IResult<ushort> IJsonUtil::fromJson<ushort>(const QJsonValue& value){
    bool ok;
    auto val = IConvertUtil::toUShort(value, ok);
    return {val, ok};
}

template<>
inline bool IJsonUtil::fromJson<bool>(const QJsonValue& value, bool& ok){
    return IConvertUtil::toBool(value, ok);
}
template<>
inline IResult<bool> IJsonUtil::fromJson<bool>(const QJsonValue& value){
    bool ok;
    auto val = IConvertUtil::toBool(value, ok);
    return {val, ok};
}

template<>
inline QString IJsonUtil::fromJson<QString>(const QJsonValue& json, bool& ok){
    return IConvertUtil::toString(json, ok);
}

template<>
inline IResult<QString> IJsonUtil::fromJson<QString>(const QJsonValue& value){
    bool ok;
    auto val = IConvertUtil::toString(value, ok);
    return {val, ok};
}

template<>
inline QStringList IJsonUtil::fromJson<QStringList>(const QJsonValue& json, bool& ok){
    return IConvertUtil::toStringList(json, ok);
}

template<>
inline IResult<QStringList> IJsonUtil::fromJson<QStringList>(const QJsonValue& value){
    bool ok;
    auto val = IConvertUtil::toStringList(value, ok);
    return {val, ok};
}

template<>
inline QJsonObject IJsonUtil::fromJson<QJsonObject>(const QJsonValue& value, bool& ok){
    return IJsonUtil::toJsonObject(value, ok);
}
template<>
inline IResult<QJsonObject> IJsonUtil::fromJson<QJsonObject>(const QJsonValue& value){
    bool ok;
    auto val = fromJson<QJsonObject>(value, ok);
    return {val, ok};
}

template<>
inline QJsonArray IJsonUtil::fromJson<QJsonArray>(const QJsonValue& value, bool& ok){
    return IJsonUtil::toJsonArray(value, ok);
}
template<>
inline IResult<QJsonArray> IJsonUtil::fromJson<QJsonArray>(const QJsonValue& value){
    bool ok;
    auto val = fromJson<QJsonArray>(value, ok);
    return {val, ok};
}

template<>
inline QJsonValue IJsonUtil::fromJson<QJsonValue>(const QJsonValue& value, bool& ok){
    return IJsonUtil::toJsonValue(value, ok);
}
template<>
inline IResult<QJsonValue> IJsonUtil::fromJson<QJsonValue>(const QJsonValue& value){
    bool ok;
    auto val = fromJson<QJsonArray>(value, ok);
    return {val, ok};
}

$PackageWebCoreEnd
