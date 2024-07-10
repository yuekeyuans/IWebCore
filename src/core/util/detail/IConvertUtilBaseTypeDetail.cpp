#pragma once

#include "core/util/IConvertUtil2.h"
#include <type_traits>

$PackageWebCoreBegin

namespace IConvertUtil2{


// number <=> string

template<>
IResult<QString> convertTo<QString>(int arg)
{
    return {QString::number(arg), true};
}

template<>
IResult<std::string> convertTo<std::string>(int arg)
{
    IResult<QString> value = convertTo<QString>(arg);
    return {value.value().toStdString(), value.isOk()};
}

// string <=> bool
template<>
IResult<QString> convertTo<QString>(bool arg) {
    return {arg ? "true" : "false", true};
}
template<>
IResult<std::string> convertTo<std::string>(bool arg)
{
    return {arg ? "true" : "false", true};
}
template<>
IResult<QByteArray> convertTo<QByteArray>(bool arg)
{
    return {arg ? "true" : "false", true};
}
template<>
IResult<bool> convertTo<bool>(const QString& value)
{
    return {value == "true", true};
}
template<>
IResult<bool> convertTo<bool>(const char* value)
{
    return convertTo<bool, QString>(value);
}
template<>
IResult<bool> convertTo<bool>(const QByteArray& data)
{
    return convertTo<bool, QString>(data);
}
template<>
IResult<bool> convertTo<bool>(IStringView data)
{
    return convertTo<bool, QString>(data.toQString());
}


}

$PackageWebCoreEnd
