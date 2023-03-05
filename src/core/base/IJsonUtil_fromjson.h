#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IToeUtil.h"
#include "core/base/IJsonUtil.h"

$PackageWebCoreBegin

namespace IJsonUtil
{
template<typename T>
T fromJson(QJsonValue, bool* ok);

template<>
int fromJson<int>(QJsonValue, bool* ok);

template<>
ushort fromJson<ushort>(QJsonValue, bool* ok);

template<>
QString fromJson<QString>(QJsonValue, bool *ok);

}

// TODO: directly copy, this should be changed;
#include "core/base/IConvertUtil.h"

template<>
inline int IJsonUtil::fromJson<int>(QJsonValue value, bool* ok){
    return IConvertUtil::toInt(value, ok);
}

template<>
inline ushort IJsonUtil::fromJson<ushort>(QJsonValue value, bool* ok){
    return IConvertUtil::toUShort(value, ok);
}

template<>
inline QString IJsonUtil::fromJson<QString>(QJsonValue json, bool* ok){
    Q_UNUSED(ok)
    Q_UNUSED(json)
//    return IJsonUtil::toString(json);
//    return IConvertUtil::toString(value, ok);
  return "127.0.0.2";
}

$PackageWebCoreEnd
