#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/ITraitUtil.h"

$PackageWebCoreBegin
$IPackageBegin(IJsonUtil)

// list / vector // TODO: optimised it!!!
#define PP_FROM_JSON_SEQUENCE_CONTAINER(Type)                    \
template<typename T>                                             \
    bool fromJson( Type <T>* ptr, const IJson& json)             \
    {                                                            \
        if(!ptr) return false;                                   \
        if(!json.is_array()) return false;                       \
                                                                 \
        for(const IJson& val : json){                            \
            T bean;                                              \
            if(!(fromJson(&bean, val)))  return false;           \
            ptr->push_back(bean);                     \
        }                                                        \
        return true;                                             \
    }
    PP_FROM_JSON_SEQUENCE_CONTAINER(QList)
    PP_FROM_JSON_SEQUENCE_CONTAINER(QVector)
    PP_FROM_JSON_SEQUENCE_CONTAINER(std::list)
    PP_FROM_JSON_SEQUENCE_CONTAINER(std::vector)
#undef PP_FROM_JSON_SEQUENCE_CONTAINER

// maps
template<typename T>
bool fromJson(QMap<QString, T>* ptr, const IJson& json)
{
    if(!ptr) return false;
    if(!json.is_object()) return false;
    for(auto& [key, value] : json.items()){
        T bean;
        if(IJsonUtil::fromJson(&bean, value)) return false;
        (*ptr)[QString::fromStdString(key)] = std::move(bean);
    }
    return true;
}

template<typename T>
bool fromJson(QMap<std::string, T>* ptr, const IJson& json)
{
    if(!ptr) return false;
    if(!json.is_object()) return false;
    for(auto& [key, value] : json.items()){
        T bean;
        if(IJsonUtil::fromJson(&bean, value)) return false;
        (*ptr)[key] = std::move(bean);
    }
    return true;
}

template<typename T>
bool fromJson(QMap<IString, T>* ptr, const IJson& json)
{
    if(!ptr) return false;
    if(!json.is_object()) return false;
    for(auto& [key, value] : json.items()){
        T bean;
        if(IJsonUtil::fromJson(&bean, value)) return false;
        IString keyVal = &key;
        keyVal.solidify();
        (*ptr)[keyVal] = std::move(bean);
    }
    return true;
}


template<typename T>
bool fromJson(std::map<QString, T>* ptr, const IJson& json)
{
    if(!ptr) return false;
    if(!json.is_object()) return false;
    for(auto& [key, value] : json.items()){
        T bean;
        if(IJsonUtil::fromJson(&bean, value)) return false;
        (*ptr)[QString::fromStdString(key)] = std::move(bean);
    }
    return true;
}

template<typename T>
bool fromJson(std::map<std::string, T>* ptr, const IJson& json)
{
    if(!ptr) return false;
    if(!json.is_object()) return false;
    for(auto& [key, value] : json.items()){
        T bean;
        if(IJsonUtil::fromJson(&bean, value)) return false;
        (*ptr)[key] = std::move(bean);
    }
    return true;
}

template<typename T>
bool fromJson(std::map<IString, T>* ptr, const IJson& json)
{
    if(!ptr) return false;
    if(!json.is_object()) return false;
    for(auto& [key, value] : json.items()){
        T bean;
        if(IJsonUtil::fromJson(&bean, value)) return false;
        IString keyVal = &key;
        keyVal.solidify();
        (*ptr)[keyVal] = std::move(bean);
    }
    return true;
}


// beans
template<typename T>
std::enable_if_t<ITraitUtil::has_class_member_loadJson_v<T>, bool>
fromJson(T* ptr, const IJson& json)
{
    if(!ptr) return false;
    if(json.is_discarded() || json.is_null()) return false;
    return ptr->loadJson(json);
}

// bool
template<typename T>
std::enable_if_t<std::is_same_v<bool, T>>
fromJson(T* ptr, const IJson& json)
{
    if(!ptr) return false;
    if(!json.is_boolean()) return false;
    *ptr = json.get<bool>();
    return true;
}

// QString
template<typename T>
std::enable_if_t<std::is_same_v<QString, T>, bool>
fromJson(T* ptr, const IJson& json)
{
    if(!ptr) return false;
    if(!json.is_string()) return false;
    *ptr = QString::fromStdString(json.get<std::string>());
    return true;
}

// std::string
template<typename T>
std::enable_if_t<std::is_same_v<std::string, T>, bool>
fromJson(T* ptr, const IJson& json)
{
    if(!ptr) return false;
    if(!json.is_string()) return false;
    *ptr = json.get<std::string>();
    return true;
}

// arithmetic
template <typename T>
std::enable_if_t<std::is_arithmetic_v<T>, bool>
fromJson(T* ptr, const IJson& json) {
    if (!ptr) return false;
    if (!json.is_number()) return false;

    try {
        if constexpr (std::is_integral_v<T>) {
            if (json.is_number_integer() || json.is_number_float()) {
                auto value = json.get<double>(); // 先以浮点数形式获取值
                if (value >= std::numeric_limits<T>::min() && value <= std::numeric_limits<T>::max()) {
                    *ptr = static_cast<T>(value); // 范围内则安全转换
                    return true;
                }
            }
        }
        // 判断是否为浮点型
        else if constexpr (std::is_floating_point_v<T>) {
            if (json.is_number_float() || json.is_number_integer()) {
                auto value = json.get<double>(); // 先以浮点数形式获取值
                if (value >= -std::numeric_limits<T>::max() && value <= std::numeric_limits<T>::max()) {
                    *ptr = static_cast<T>(value); // 范围内则安全转换
                    return true;
                }
            }
        }
    } catch (...) {
        return false;
    }
    return false;
}

$IPackageEnd(IJsonUtil)
$PackageWebCoreEnd
