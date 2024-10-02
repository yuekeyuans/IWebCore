#pragma once

#include "core/util/IPreProcessorUtil.h"
#include "core/util/ITraitUtil.h"
#include "core/bean/IBeanAbort.h"
#include <typeinfo>

namespace detail{

template<typename T>
IJson readJsonOfPlainType(T value)
{
    return value;
}

template<typename T>
IJson readJsonOfQStringType(const T& value)
{
    return value.toStdString();
}

template<typename T>
IJson readJsonOfQStringListType(const T& value)
{
    IJson array = IJson::array();
    for(const QString& val : value){
        array.push_back(val.toStdString());
    }
    return array;
}

template<typename T>
IJson readJsonOfStdVectorType( const T& value )
{
    IJson array = IJson::array();
    for(const auto& name : value){
        array.push_back(toJson( name ));
    }
    return array;
}

template<typename T>
IJson readJsonOfQVectorType( const T& value)
{
    IJson array = IJson::array();
    for(const auto& val : value){
        array.emplace_back(toJson(val));
    }
    return array;
}

template<typename T>
IJson readJsonOfStdStringMapType(const T& value)
{
    IJson obj = IJson::object();
    for (const auto& pair : value) {
        obj[pair.first] = toJson(pair.second);
    }
    return obj;
}

template<typename T>
IJson readJsonOfQStringMapType(const T& value)
{
    IJson obj = IJson::object();
    for(const auto& it=value.cbegin(); it!=value.cend(); it++){
        obj[it->key().toStdString()] = toJson(it->value());
    }
    return obj;
}

template<typename T>
IJson readJsonOfBeanType( const T& value)
{
    return value.toJson();
}

template<typename T>
void readJsonOfAssertError(const char* data)
{
    IBeanAbort::abortInvalidBeanEmbededBeanType(typeid(T).name());
}

template<typename T>
IJson toJson(const T& value)
{
    if constexpr (std::is_arithmetic_v<T>){
        return detail::readJsonOfPlainType( value );
    } else if constexpr (std::is_same_v<std::string, T >){
        return detail::readJsonOfPlainType( value );
    }else if constexpr( std::is_same_v<IJson, T>){
        return detail::readJsonOfPlainType(value);
    } else if constexpr (std::is_same_v<QString, T >) {
        return detail::readJsonOfQStringType< T >( value );
    } else if constexpr (std::is_same_v<QStringList, T >){
        return detail::readJsonOfQStringListType< T >( value );
    } else if constexpr ( ITraitUtil::is_std_vector_v< T >){
        return detail::readJsonOfStdVectorType< T >( value );
    } else if constexpr (ITraitUtil::is_q_vector_v< T >){
        return detail::readJsonOfQVectorType< T >( value );
    } else if constexpr (ITraitUtil::is_std_string_map_v< T >) {
        return detail::readJsonOfStdStringMapType< T > ( value );
    } else if constexpr (ITraitUtil::is_q_string_map_v< T >){
        return detail::readJsonOfQStringMapType< T >( value );
    } else if constexpr (ITraitUtil::has_class_member_toJson_v< T >){
        return detail::readJsonOfBeanType< T > ( value );
    } else{
        IBeanAbort::abortInvalidBeanEmbededBeanType(typeid(T).name());
    }
}

template<typename T>
void writeJsonOfBoolType(T* ptr, const IJson& val)
{
    if(val.is_boolean()){
        *ptr = val.get<bool>();
    }
}

template<typename T>
void writeJsonOfNumberType(T*ptr, const IJson& val)
{
    if(val.is_number()){
        *ptr = val.get<T>();
    }
}

template<typename T>
void writeJsonOfStdStringType(T* ptr, const IJson& value){
    if(value.is_string()){
        *ptr = value.get<std::string>();
    }
}

template<typename T>
void writeJsonOfIJsonType(T* ptr, const IJson& value)
{
    *ptr = value;
}

template<typename T>
void writeJsonOfQStringType(T* ptr, const IJson& value){
    if(value.is_string()){
        *ptr = QString::fromStdString(value.get<std::string>());
    }
}

template<typename T>
void writeJsonOfQStringListType(T* ptr, const IJson& value){
    if(value.is_array()){
        QStringList data;
        for(const auto& val : value){
            if(val.is_string()){
                data.append(QString::fromStdString(val.get<std::string>()));
            }else{
                return;     // stop once error occured
            }
        }
        *ptr = data;
    }
}

// TODO: check exception
template<typename T>
void writeJsonOfStdVectorType(T* ptr, const IJson& value){
    using U = std::remove_cv_t<T::value_type>;
    if(value.is_array()){
        T data;
        for(const auto& val : value){
            U item;
            fromJson(&item, val);
            data.push_back(std::move(item));
        }
        *ptr = std::move(data);
    }
}

// TODO: check exception
template<typename T>
void writeJsonOfQVectorType(T* ptr, const IJson& value)
{
    using U = std::remove_cv_t<T::value_type>;
    if(value.is_array()){
        T data;
        for(const auto& val : value){
            U item;
            fromJson(&item, val);
            data.append(std::move(item));
        }
        *ptr = std::move(data);
    }
}


template<typename T>
void writeJsonOfStdStringMapType(T*ptr, const IJson& value)
{
    using U = std::remove_cv_t<T::mapped_type>;
    if(value.is_object()){
        T data;
        for(const auto& [key, val] : value.items()){
            U item;
            fromJson(&item, val);
            data[key] = item;
        }
        *ptr = std::move(data);
    }
}

// slow, check
template<typename T>
void writeJsonOfQStringMapType(T*ptr, const IJson& value)
{
    using U = std::remove_cv_t<T::value_type>;
    if(value.is_object()){
        T data;
        for(const auto& [key, val] : value.items()){
            U item;
            data[key] = fromJson(&item, val);
        }
        *ptr = std::move(data);
    }
}

template<typename T>
void writeJsonOfBeanType(T* ptr, const IJson& value)
{
    ptr->loadJson(value);
}

template<typename T>
void fromJson(T* ptr, const IJson& json)
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
    } else{
        IBeanAbort::abortInvalidBeanEmbededBeanType(typeid(T).name());
    }
}

}

#define $BeanFieldDeclare(type, name)                                                               \
private:                                                                                            \
    Q_PROPERTY(type name MEMBER name WRITE $write_##name##_value)                                   \
    void $write_##name##_value(const type & value){this-> name = value; }                           \
    Q_INVOKABLE IJson $##name##_toJsonValue() const {                                               \
        return detail::toJson< type > ( name );                                                     \
    }                                                                                               \
    Q_INVOKABLE void $##name##_fromJsonValue(const IJson& json) {                                   \
        detail::fromJson< type >(& name, json);                                                     \
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
