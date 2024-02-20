#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IToeUtil.h"
#include "core/base/IJsonUtil.h"

$PackageWebCoreBegin

namespace IJsonUtil
{
template<typename T>
T fromJson(const QJsonValue&, bool* ok);

template<>
int fromJson<int>(const QJsonValue&, bool* ok);

template<>
ushort fromJson<ushort>(const QJsonValue&, bool* ok);

template<>
QString fromJson<QString>(const QJsonValue&, bool *ok);

template<>
bool fromJson<bool>(const QJsonValue&, bool*ok);

}

// TODO: directly copy, this should be changed;
#include "core/base/IConvertUtil.h"

template<>
inline int IJsonUtil::fromJson<int>(const QJsonValue& value, bool* ok){
    return IConvertUtil::toInt(value, ok);
}

template<>
inline ushort IJsonUtil::fromJson<ushort>(const QJsonValue& value, bool* ok){
    return IConvertUtil::toUShort(value, ok);
}

template<>
inline QString IJsonUtil::fromJson<QString>(const QJsonValue& json, bool* ok){
    return IConvertUtil::toString(json, ok);
}

template<>
inline bool IJsonUtil::fromJson<bool>(const QJsonValue& value, bool* ok){
    return IConvertUtil::toBool(value, ok);
}

$PackageWebCoreEnd
