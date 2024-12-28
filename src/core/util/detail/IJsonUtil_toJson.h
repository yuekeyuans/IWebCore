#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/ITraitUtil.h"

$PackageWebCoreBegin
$IPackageBegin(IJsonUtil)

// list vector
#define PP_TO_JSON_SEQUENCE_CONTAINER(klass)                    \
    template<typename T>                                        \
    IJson toJson(const klass <T>& value){                       \
        IJson result = IJson::array();                          \
        for(const T& val :value){                               \
            result.push_back(toJson(val));                      \
        }                                                       \
        return result;                                          \
    }
    PP_TO_JSON_SEQUENCE_CONTAINER(std::list)
    PP_TO_JSON_SEQUENCE_CONTAINER(std::vector)
    PP_TO_JSON_SEQUENCE_CONTAINER(QList)
    PP_TO_JSON_SEQUENCE_CONTAINER(QVector)
#undef PP_TO_JSON_SEQUENCE_CONTAINER

// beans
template<typename T>
std::enable_if_t<ITraitUtil::has_class_member_toJson_v<T>, IJson> toJson(const T& value)
{
    return value.toJson();
}

// map
template<typename T, typename U>
IJson toJson(const std::map<T, U>& map)
{
    constexpr bool c_valid = std::is_same_v<T, std::string>
            || std::is_same_v<T, QString>
            || std::is_same_v<T, IString>
            || std::is_floating_point_v<T>
            || std::is_arithmetic_v<T>;
    static_assert(c_valid, "std::map key only support number, QString, std::string and IString");

    IJson result = IJson::object();
    for (auto it = map.cbegin(); it != map.cend(); ++it) {
        if constexpr (std::is_same_v<T, std::string>){
            result[it->first] = toJson(it->second);
        }else if constexpr (std::is_same_v<T, QString>){
            result[it->first.toStdString()] = toJson(it->second);
        }else if constexpr(std::is_same_v<T, IStringView>){
            result[std::string(it->first)] = toJson(it->second);
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
            || std::is_same_v<T, IStringView>
            || std::is_same_v<T, IString>
            || std::is_floating_point_v<T>
            || std::is_arithmetic_v<T>;
    static_assert(c_valid, "std::map key only support number, QString, std::string, IString");

    IJson result = IJson::object();
    for (auto it = map.cbegin(); it != map.cend(); ++it) {
        if constexpr (std::is_same_v<T, std::string>){
            result[it.key()] = toJson(it.value());
        }else if constexpr (std::is_same_v<T, QString>){
            result[it.key().toStdString()] = toJson(it.value());
        }else if constexpr (std::is_same_v<T, IStringView>){
            result[std::string(it.key())] = toJson(it.value());
        }else{
            result[std::to_string(it.key())] = toJson(it.value());
        }
    }
    return result;
}

template<typename T>
std::enable_if_t<std::is_arithmetic_v<T> || std::is_same_v<T, const char*>, IJson>
toJson(const T& value)
{
    return value;
}

inline IJson toJson(bool value){ return value;}
inline IJson toJson(std::string&& value) {return std::move(value);}
inline IJson toJson(const std::string& value) {return value;}
inline IJson toJson(const QString& value) {return value.toStdString();}
inline IJson toJson(const IString& value){return value.toStdString();}
inline IJson toJson(IJson&& value) {return std::move(value);}
inline IJson toJson(const IJson& value){return value;}
inline IJson toJson(const QStringList& value)
{
    IJson array = IJson::array();
    for(const QString& val : value){
        array.push_back(val.toStdString());
    }
    return array;
}

$IPackageEnd(IJsonUtil)
$PackageWebCoreEnd
