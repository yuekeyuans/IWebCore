#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/ITraitUtil.h"

$PackageWebCoreBegin
$IPackageBegin(IJsonUtil)

// list / vector
#define PP_FROM_JSON_SEQUENCE_CONTAINER(Type)                                   \
    template<typename T>                                                        \
    bool fromJson( Type <T>& data, const IJson& json)                           \
    {                                                                           \
        if(!json.is_array()) return false;                                      \
        for(const IJson& val : json){                                           \
            T bean;                                                             \
            if(!(fromJson(bean, val)))  return false;                           \
            data.push_back(std::move(bean));                                    \
        }                                                                       \
        return true;                                                            \
    }
    PP_FROM_JSON_SEQUENCE_CONTAINER(QList)
    PP_FROM_JSON_SEQUENCE_CONTAINER(QVector)
    PP_FROM_JSON_SEQUENCE_CONTAINER(std::list)
    PP_FROM_JSON_SEQUENCE_CONTAINER(std::vector)
#undef PP_FROM_JSON_SEQUENCE_CONTAINER

// beans
template<typename T>
std::enable_if_t<ITraitUtil::has_class_member_loadJson_v<T>, bool>
fromJson(T& data, const IJson& json)
{
    if(json.is_discarded() || json.is_null()) return false;
    return data.loadJson(json);
}

template<typename T, typename U>
bool fromJson(std::map <T, U>& data, const IJson& json)
{
    constexpr bool c_valid = std::is_same_v<T, std::string>
            || std::is_same_v<T, QString>
            || std::is_same_v<T, IString>;
    static_assert(c_valid, "std::map key only support QString, std::string and IString");

    if(!json.is_object()) return false;
    for(auto& [key, value] : json.items()){
        U bean;
        if(!IJsonUtil::fromJson(bean, value)) return false;
        if constexpr (std::is_same_v<T, std::string>){
            data[key] = std::move(bean);
        }else if constexpr(std::is_same_v<T, QString>){
            data[QString::fromStdString(key)] = std::move(bean);
        }else if constexpr( std::is_same_v<T, IString>){
            IString keyVal = &key;
            keyVal.solidify();
            data[keyVal] = std::move(bean);
        }
    }
    return true;
}

template<typename T, typename U>
bool fromJson(QMap <T, U>& data, const IJson& json)
{
    constexpr bool c_valid = std::is_same_v<T, std::string>
            || std::is_same_v<T, QString>
            || std::is_same_v<T, IString>;
    static_assert(c_valid, "QMap key only support QString, std::string and IString");


    if(!json.is_object()) return false;
    for(auto& [key, value] : json.items()){
        U bean;
        if(!IJsonUtil::fromJson(bean, value)) return false;
        if constexpr (std::is_same_v<T, std::string>){
            data[key] = std::move(bean);
        }else if constexpr(std::is_same_v<T, QString>){
            data[QString::fromStdString(key)] = std::move(bean);
        }else if constexpr( std::is_same_v<T, IString>){
            IString keyVal = &key;
            keyVal.solidify();
            data[keyVal] = std::move(bean);
        }
    }
    return true;
}


// arithmetic
template <typename T>
std::enable_if_t<std::is_arithmetic_v<T>, bool>
fromJson(T& data, const IJson& json) {
//    if (!data) return false;
    if (!json.is_number()) return false;

    try {
        if constexpr (std::is_integral_v<T>) {
            if (json.is_number_integer() || json.is_number_float()) {
                auto value = json.get<double>(); // 先以浮点数形式获取值
                if (value >= std::numeric_limits<T>::min() && value <= std::numeric_limits<T>::max()) {
                    data = static_cast<T>(value); // 范围内则安全转换
                    return true;
                }
            }
        }
        // 判断是否为浮点型
        else if constexpr (std::is_floating_point_v<T>) {
            if (json.is_number_float() || json.is_number_integer()) {
                auto value = json.get<double>(); // 先以浮点数形式获取值
                if (value >= -std::numeric_limits<T>::max() && value <= std::numeric_limits<T>::max()) {
                    data = static_cast<T>(value); // 范围内则安全转换
                    return true;
                }
            }
        }
    } catch (...) {
        return false;
    }
    return false;
}

inline bool fromJson(bool& data, const IJson& json)
{
    if(!json.is_boolean()) return false;
    data = json.get<bool>();
    return true;
}

inline bool fromJson(QString& data, const IJson& json)
{
    if(!json.is_string()) return false;
    data = QString::fromStdString(json.get<std::string>());
    return true;
}

inline bool fromJson(std::string& data, const IJson& json)
{
    if(!json.is_string()) return false;
    data = json.get<std::string>();
    return true;
}

inline bool fromJson(IString& data, const IJson& json)
{
    if(!json.is_string()) return false;
    data = json.get<std::string>();
    return true;
}

inline bool fromJson(IJson& value, const IJson& json)
{
    value = json;
    return true;
}

inline bool fromJson(QStringList& value, const IJson& json)
{
    if(!json.is_array()) return false;
    value.clear();
    for(auto val : json){
        if(!val.is_string()) return false;
        value.append(QString::fromStdString(val.get<std::string>()));
    }
    return true;
}

$IPackageEnd(IJsonUtil)
$PackageWebCoreEnd
