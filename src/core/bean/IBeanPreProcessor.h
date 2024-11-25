#pragma once

#include "core/util/IPreProcessorUtil.h"
#include "core/util/ITraitUtil.h"
#include "core/util/IJsonUtil.h"
#include "core/bean/IBeanAbort.h"
#include "core/bean/IBeanTypeManage.h"
#include <typeinfo>

$PackageWebCoreBegin

namespace detail{

template<typename T>
bool writeJsonOfBoolType(T* ptr, const IJson& val)
{
    if(val.is_boolean()){
        *ptr = val.get<bool>();
        return true;
    }
    return false;
}

template<typename T>
bool writeJsonOfNumberType(T*ptr, const IJson& val)
{
    if(val.is_number()){
        *ptr = val.get<T>();
        return true;
    }
    return false;
}

template<typename T>
bool writeJsonOfStdStringType(T* ptr, const IJson& value){
    if(value.is_string()){
        *ptr = value.get<std::string>();
        return true;
    }
    return false;
}

template<typename T>
bool writeJsonOfIJsonType(T* ptr, const IJson& value)
{
    *ptr = value;
    return true;
}

template<typename T>
bool writeJsonOfQStringType(T* ptr, const IJson& value){
    if(value.is_string()){
        *ptr = QString::fromStdString(value.get<std::string>());
        return true;
    }
    return false;
}

template<typename T>
bool writeJsonOfQStringListType(T* ptr, const IJson& value){
    if(value.is_array()){
        QStringList data;
        for(const auto& val : value){
            if(val.is_string()){
                data.append(QString::fromStdString(val.get<std::string>()));
            }else{
                return false;     // stop once error occured
            }
        }
        *ptr = data;
        return true;
    }
    return false;
}

// TODO: check exception
template<typename T>
bool writeJsonOfStdVectorType(T* ptr, const IJson& value){
    using U = std::remove_cv_t<T::value_type>;
    if(value.is_array()){
        T data;
        for(const auto& val : value){
            U item;
            if(fromJson(&item, val)){
                data.push_back(std::move(item));
            }else{
                return false;
            }
        }
        *ptr = std::move(data);
        return true;
    }
    return false;
}

// TODO: check exception
template<typename T>
bool writeJsonOfQVectorType(T* ptr, const IJson& value)
{
    using U = std::remove_cv_t<T::value_type>;
    if(value.is_array()){
        T data;
        for(const auto& val : value){
            U item;
            if(fromJson(&item, val)){
                data.append(std::move(item));
            }else{
                return false;
            }
        }
        *ptr = std::move(data);
        return true;
    }
    return false;
}


template<typename T>
bool writeJsonOfStdStringMapType(T*ptr, const IJson& value)
{
    using U = std::remove_cv_t<T::mapped_type>;
    if(value.is_object()){
        T data;
        for(const auto& [key, val] : value.items()){
            U item;
            if(fromJson(&item, val)){
                data[key] = std::move(item);
            }else{
                return false;
            }
        }
        *ptr = std::move(data);
        return true;
    }
    return false;
}

// slow, check
template<typename T>
bool writeJsonOfQStringMapType(T*ptr, const IJson& value)
{
    using U = std::remove_cv_t<T::value_type>;
    if(value.is_object()){
        T data;
        for(const auto& [key, val] : value.items()){
            U item;
            if(fromJson(&item, val)){
                data[key] = std::move(item);
            }else{
                return false;
            }
        }
        *ptr = std::move(data);
        reutrn true;
    }
    return false;
}

template<typename T>
bool writeJsonOfBeanType(T* ptr, const IJson& value)
{
    return ptr->loadJson(value);
}

template<typename T>
bool fromJson(T* ptr, const IJson& json)
{
    if constexpr (std::is_same_v<T, bool>){
        return detail::writeJsonOfBoolType(ptr, json);
    }else if constexpr (std::is_floating_point_v<T> || std::is_integral_v<T>){
        return detail::writeJsonOfNumberType(ptr, json );
    } else if constexpr (std::is_same_v<std::string, T >){
        return detail::writeJsonOfStdStringType( ptr, json );
    }else if constexpr( std::is_same_v<IJson, T>){
        return detail::writeJsonOfIJsonType(ptr, json);
    } else if constexpr (std::is_same_v<QString, T >) {
        return detail::writeJsonOfQStringType< T >( ptr, json );
    } else if constexpr (std::is_same_v<QStringList, T >){
        return detail::writeJsonOfQStringListType< T >( ptr, json );
    } else if constexpr ( ITraitUtil::is_std_vector_v< T >){
        return detail::writeJsonOfStdVectorType< T >( ptr, json );
    } else if constexpr (ITraitUtil::is_q_vector_v< T >){
        return detail::writeJsonOfQVectorType< T >( ptr, json );
    } else if constexpr (ITraitUtil::is_std_string_map_v< T >) {
        return detail::writeJsonOfStdStringMapType< T > ( ptr, json );
    } else if constexpr (ITraitUtil::is_q_string_map_v< T >){
        return detail::writeJsonOfQStringMapType< T >( ptr, json );
    } else if constexpr (ITraitUtil::has_class_member_toJson_v< T >){
        return detail::writeJsonOfBeanType< T > ( ptr, json );
    }
    return false;
}

}


$PackageWebCoreEnd

#define $BeanFieldDeclare(type, name)                                                               \
private:                                                                                            \
    Q_PROPERTY(type name MEMBER name WRITE $write_##name##_value)                                   \
    void $write_##name##_value(const type & value){this-> name = value; }                           \
    Q_INVOKABLE IJson $##name##_toJsonValue() const {                                               \
        return IJsonUtil::toJson( name );                                                           \
    }                                                                                               \
    Q_INVOKABLE bool $##name##_fromJsonValue(const IJson& json) {                                   \
        return detail::fromJson< type >(& name, json);                                              \
    }                                                                                               \
public:

#define $BeanField_2(type, name) \
    type name {};                \
    $BeanFieldDeclare(type, name)

#define $BeanField_3(type, name, value1) \
    $BeanFieldDeclare(type, name) \
    type name {value1};

#define $BeanField_4(type, name, value1, value2) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2};

#define $BeanField_5(type, name, value1, value2, value3) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3};

#define $BeanField_6(type, name, value1, value2, value3, value4) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4};

#define $BeanField_7(type, name, value1, value2, value3, value4, value5) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4, value5};

#define $BeanField_8(type, name, value1, value2, value3, value4, value5, value6) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4, value5, value6};

#define $BeanField_9(type, name, value1, value2, value3, value4, value5, value6, value7) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4, value5, value6, value7};

#define $BeanField_10(type, name, value1, value2, value3, value4, value5, value6, value7, value8) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4, value5, value6, value7, value8};

#define $BeanField_11(type, name, value1, value2, value3, value4, value5, value6, value7, value8, value9) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4, value5, value6, value7, value8, value9};

#define $BeanField_12(type, name, value1, value2, value3, value4, value5, value6, value7, value8, value9, value10) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4, value5, value6, value7, value8, value9, value10};

#define $BeanField_(N) $BeanField_##N
#define $BeanField_EVAL(N) $BeanField_(N)
#define $BeanField(...) PP_EXPAND( $BeanField_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )
