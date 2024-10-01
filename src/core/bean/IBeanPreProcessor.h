#pragma once

#include "core/util/IPreProcessorUtil.h"
#include "core/util/ITraitUtil.h"
#include "core/bean/IBeanAbort.h"
#include <typeinfo>

namespace detail{

template<typename T>
IJson WrapPlainType(T value)
{
    return value;
}

template<typename T>
IJson WrapQStringType(const T& value)
{
    return value.toStdString();
}

template<typename T>
IJson WrapQStringListType(const T& value)
{
    IJson array = IJson::array();
    for(const QString& val : value){
        array.push_back(val.toStdString());
    }
    return array;
}

template<typename T>
IJson WrapStdVectorType( const T& value )
{
    IJson array = IJson::array();
    for(const auto& name : value){
        array.push_back(toJson( name ));
    }
    return array;
}

template<typename T>
IJson WrapQVectorType( const T& value)
{
    IJson array = IJson::array();
    for(const auto& val : value){
        array.emplace_back(toJson(val));
    }
    return array;
}

template<typename T>
IJson WrapStdStringMapType(const T& value)
{
    IJson obj = IJson::object();
    for (const auto& pair : value) {
        obj[pair.first] = toJson(pair.second);
    }
    return obj;
}

template<typename T>
IJson WrapQStringMapType(const T& value)
{
    IJson obj = IJson::object();
    for(const auto& it=value.cbegin(); it!=value.cend(); it++){
        obj[it->key().toStdString()] = toJson(it->value());
    }
    return obj;
}

template<typename T>
IJson WrapBeanType( const T& value)
{
    return value.toJson();
}

template<typename T>
void WrapAssertError(const char* data)
{
    IBeanAbort::abortInvalidBeanEmbededBeanType(typeid(T).name());
}

template<typename T>
IJson toJson(const T& value)
{
    if constexpr (std::is_arithmetic_v<T>){
        return detail::WrapPlainType( value );
    } else if constexpr (std::is_same_v<std::string, T >){
        return detail::WrapPlainType( value );
    }else if constexpr( std::is_same_v<IJson, T>){
        return detail::WrapPlainType(value);
    } else if constexpr (std::is_same_v<QString, T >) {
        return detail::WrapQStringType< T >( value );
    } else if constexpr (std::is_same_v<QStringList, T >){
        return detail::WrapQStringListType< T >( value );
    } else if constexpr ( ITraitUtil::is_std_vector_v< T >){
        return detail::WrapStdVectorType< T >( value );
    } else if constexpr (ITraitUtil::is_q_vector_v< T >){
        return detail::WrapQVectorType< T >( value );
    } else if constexpr (ITraitUtil::is_std_string_map_v< T >) {
        return detail::WrapStdStringMapType< T > ( value );
    } else if constexpr (ITraitUtil::is_q_string_map_v< T >){
        return detail::WrapQStringMapType< T >( value );
    } else if constexpr (ITraitUtil::has_class_member_toJson_v< T >){
        return detail::WrapBeanType< T > ( value );
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
