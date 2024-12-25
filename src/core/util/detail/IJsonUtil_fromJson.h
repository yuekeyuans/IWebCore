#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/ITraitUtil.h"

$PackageWebCoreBegin
$IPackageBegin(IJsonUtil)

//template<typename T>
//bool fromJson(T, const IJson&);

//template<typename T>
//bool  fromJson(T *ptr, const IJson &json)
//{
//    return ptr->loadJson(json);
//}

template<typename T>
std::enable_if_t<ITraitUtil::has_class_member_loadJson_v<T>, bool>
fromJson(T* ptr, const IJson& json)
{
    if(!ptr) return false;
    if(json.is_discarded() || json.is_null()) return false;
    return ptr->loadJson(json);
}

template<typename T>
bool fromJson(QList<T>* ptr, const IJson& json)
{
    if(!ptr) return false;
    if(!json.is_array()) return false;      // TODO: 这个是否可以为空

    for(const IJson& val : json){
        T bean;
        if(!(fromJson(&bean, val))){
            return false;
        }
        ptr->append(bean);
    }
    return true;
}

template<typename T>
std::enable_if_t<std::is_same_v<bool, T>>
fromJson(T* ptr, const IJson& json)
{
    if(!ptr) return false;
    if(!json.is_boolean()) return false;
    *ptr = json.get<bool>();
    return true;
}

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
