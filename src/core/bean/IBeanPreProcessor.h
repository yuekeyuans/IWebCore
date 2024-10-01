#pragma once

#include "core/util/IPreProcessorUtil.h"
#include "core/util/ITraitUtil.h"

namespace detail{

template<typename T>
IJson WrapPlainType(T value) {
    return value;
}

template<typename T>
IJson WrapQStringType(const T& value){
    return value.toStdString();
}

template<typename T>
IJson WrapQStringListType(const T& value){
    IJson array = IJson::array();
    for(const QString& val : value){
        array.push_back(val.toStdString());
    }
    return array;
}

template<typename T>
IJson WrapStdVectorType( const T& value ){
    IJson array = IJson::array();
    for(const T& name : value){
        if constexpr (std::is_arithmetic_v< T >){
            array.push_back( detail::WrapPlainType( name ) );
        } else if constexpr (std::is_same_v<std::string, T >){
            array.push_back( detail::WrapPlainType( name ) );
        } else if constexpr (std::is_same_v<QString, T >) {
            array.push_back( detail::WrapQStringType< T >( name ));
        } else if constexpr (std::is_same_v<QStringList, T >){
            array.push_back( detail::WrapQStringListType< T >( name ));
        } else if constexpr (ITraitUtil::is_std_vector_v< T >){
            array.push_back( detail::WrapStdVectorType<T>(name));
        } else{
            qDebug() << "failed type" << typeid(T).name();
        }
        return 1;
    }
    return array;
}

template<typename T>
IJson WrapBeanType( const T& value){
    return value.toJson();
}

//template<typename T>
//IJson WrapQVectorType( const T& value){
//    return 1;
//}

//template<typename T>
//IJson WrapStdMapType(const T& value){
//    return 2;
//}

//template<typename T>
//IJson WrapQMapType(const T& value){
//    return 3;
//}

}

#define $BeanFieldDeclare(type, name)                                              \
    Q_PROPERTY(type name MEMBER name WRITE $write_##name##_value)                  \
    void $write_##name##_value(const type & value){this-> name = value; }          \
    Q_INVOKABLE IJson $##name##_toJsonValue() const {                              \
        if constexpr (std::is_arithmetic_v< type >){                               \
            return detail::WrapPlainType( name );                                  \
        } else if constexpr (std::is_same_v<std::string, type >){                  \
            return detail::WrapPlainType( name );                                  \
        } else if constexpr (std::is_same_v<QString, type >) {                     \
            return detail::WrapQStringType< type >( name );                        \
        } else if constexpr (std::is_same_v<QStringList, type >){                  \
            return detail::WrapQStringListType< type >( name );                    \
        } else if constexpr ( ITraitUtil::is_std_vector_v< type >){                \
            return detail::WrapStdVectorType< type >( name );                      \
        } else if constexpr (ITraitUtil::$HAS_CLASS_MEMBER_toJson< type >::value){ \
            return detail::WrapBeanType< type > ( name );                          \
        }                                                                          \
                                                                                   \
            else{                                                                  \
            qDebug() << "failed" << #name << #type;                                \
            return nullptr;                                                        \
        }                                                                          \
    }



//#define $BeanFieldDeclare(type, name)                                              \
//    Q_PROPERTY(type name MEMBER name WRITE $write_##name##_value)                  \
//    void $write_##name##_value(const type & value){this-> name = value; }          \
//    Q_INVOKABLE IJson $##name##_toJsonValue() const {                              \
//        if constexpr (std::is_arithmetic_v< type >){                               \
//            return detail::WrapPlainType( name );                                  \
//        } else if constexpr (std::is_same_v<std::string, type >){                  \
//            return detail::WrapPlainType( name );                                  \
//        } else if constexpr (std::is_same_v<QString, type >) {                     \
//            return detail::WrapQStringType< type >( name );                        \
//        } else if constexpr (std::is_same_v<QStringList, type >){                  \
//            return detail::WrapQStringListType< type >( name );                    \
//        } else if constexpr (ITraitUtil::is_std_vector_v< type >){                 \
//            return detail::WrapStdVectorType< type >( name );                      \
//        } else{                                                                    \
//            static_assert(false, #type );                                          \
//        }                                                                          \
//    }

#define $BeanField_2(type, name) \
    $BeanFieldDeclare(type, name) \
    type name {};

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


#define $AsBeanList(klassName)                                                                         \
class klassName ## List : public QList< klassName >, public IBeanInterface< klassName ## List >        \
{                                                                                                      \
    Q_GADGET                                                                                           \
public:                                                                                                \
    virtual IJson toJson(bool *ok) const final {                                                       \
        IJson json = IJson::array();                                                                   \
        for(const klassName & bean : *this){                                                           \
            json.push_back(bean.toJson(ok));                                                           \
            if(ok != nullptr && *ok ==false){                                                          \
                return json;                                                                           \
            }                                                                                          \
        }                                                                                              \
        return json;                                                                                   \
    }                                                                                                  \
    virtual bool loadJson(const IJson &value) final{                                                   \
        if(value.is_null()){ return true; }                                                            \
        if(!value.is_array()){ return false; }                                                         \
        for(const IJson& val : value){                                                               \
            klassName bean;                                                                            \
            if(!bean.loadJson(val)){                                                                 \
                return false;                                                                          \
            }                                                                                          \
            this->append(bean);                                                                        \
        }                                                                                              \
        return true;                                                                                   \
    }                                                                                                  \
};
