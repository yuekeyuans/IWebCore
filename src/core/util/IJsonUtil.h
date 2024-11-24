#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/ITraitUtil.h"

$PackageWebCoreBegin
$IPackageBegin(IJsonUtil)

IJson toJson(bool);
IJson toJson(std::string&&);
IJson toJson(const std::string&);
IJson toJson(const QString&);

IJson toJson(IJson&&);
IJson toJson(const IJson&);


#define PP_NUMBER_LIKE_TOJSON(klass)     \
inline IJson toJson(klass value) {       \
    return value;                        \
}
PP_NUMBER_LIKE_TOJSON(char)
PP_NUMBER_LIKE_TOJSON(unsigned char)
PP_NUMBER_LIKE_TOJSON(signed char)
PP_NUMBER_LIKE_TOJSON(short)
PP_NUMBER_LIKE_TOJSON(unsigned short)
PP_NUMBER_LIKE_TOJSON(int)
PP_NUMBER_LIKE_TOJSON(unsigned int)
PP_NUMBER_LIKE_TOJSON(long)
PP_NUMBER_LIKE_TOJSON(unsigned long)
PP_NUMBER_LIKE_TOJSON(long long)
PP_NUMBER_LIKE_TOJSON(unsigned long long)
PP_NUMBER_LIKE_TOJSON(float)
PP_NUMBER_LIKE_TOJSON(double)
#undef PP_NUMBER_LIKE_TOJSON


#define PP_ARRAY_LIKE_TOJSON(klass)               \
template<typename T>                              \
IJson toJson(const klass <T>& value){             \
    IJson result = IJson::array();                \
    for(const T& val :value){                     \
        result.push_back(toJson(val));            \
    }                                             \
    return result;                                \
}                                                 \

PP_ARRAY_LIKE_TOJSON(std::list)
PP_ARRAY_LIKE_TOJSON(std::vector)
PP_ARRAY_LIKE_TOJSON(QList)
PP_ARRAY_LIKE_TOJSON(QVector)
#undef PP_ARRAY_LIKE_TOJSON

template<typename T>
std::enable_if_t< ITraitUtil::has_class_member_toJson_v<T>, IJson> toJson(T&& value)
{
    return value.toJson();
}

template<typename T, typename U>
IJson toJson(const std::map<T, U>& map)
{
    constexpr bool c_valid = std::is_same_v<T, std::string>
            || std::is_same_v<T, QString>
            || std::is_floating_point_v<T>
            || std::is_arithmetic_v<T>;
    static_assert(c_valid, "std::map key only support number, QString, std::string");

    IJson result = IJson::object();
    for (auto it = map.cbegin(); it != map.cend(); ++it) {
        if constexpr (std::is_same_v<T, std::string>){
            result[it->first] = toJson(it->second);
        }else if constexpr (std::is_same_v<T, QString>){
            result[it->first.toStdString()] = toJson(it->second);
        }else{
            result[std::to_string(it->first)] = toJson(it->second);
        }
    }
    return result;
}

template<typename T, typename U>
IJson toJson(const QMap<T, U>& map)
{
    constexpr bool c_valid = std::is_same_v<T, std::string>
            || std::is_same_v<T, QString>
            || std::is_floating_point_v<T>
            || std::is_arithmetic_v<T>;
    static_assert(c_valid, "std::map key only support number, QString, std::string");

    IJson result = IJson::object();
    for (auto it = map.cbegin(); it != map.cend(); ++it) {
        if constexpr (std::is_same_v<T, std::string>){
            result[it.key()] = toJson(it.value());
        }else if constexpr (std::is_same_v<T, QString>){
            result[it.key().toStdString()] = toJson(it.value());
        }else{
            result[std::to_string(it.key())] = toJson(it.value());
        }
    }
    return result;
}

$IPackageEnd(IJsonUtil)
$PackageWebCoreEnd
