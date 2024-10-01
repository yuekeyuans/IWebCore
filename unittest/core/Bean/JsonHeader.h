#pragma once

#include "core/util/ITraitUtil.h"
#include "core/util/IPreProcessorUtil.h"



#ifndef JSON_HEADER__PP
#define JSON_HEADER__PP

template<typename T>
struct ProcessWith;

template<typename T>
struct ProcessWith<std::vector<T>>
{
    static IJson toJson(const std::vector<T>& values){
        IJson array = IJson::array();
        for(const T& val :values){
            if constexpr (std::is_arithmetic_v< T >){
                array.push_back(IJson(val));
            } else if constexpr (std::is_same_v<std::string, T >){
                array.push_back(IJson(val));
            }  else if constexpr (ITraitUtil::is_std_vector_v< T >){
                array.push_back( WrapProcessWith<T>(val) );
            }
        }

        return array;
    }
};


template<typename T>
IJson WrapProcessWith(const T& value){
    return ProcessWith<T>::toJson(value);
}

template<typename T>
IJson WrapPlainType(const T& value){
    return value;
}

template<typename T>
IJson WrapBeanType(const T& value)
{
    bool ok;
    return value.toJson(&ok);
}


#define TO_JSON(type, name)                                                                \
    type name;                                                                             \
    Q_INVOKABLE IJson name##_toJson () const                                      \
    {                                                                                      \
        if constexpr (std::is_arithmetic_v< type >){                                           \
            return name;                                                                 \
        } else if constexpr (std::is_same_v<std::string, type >){                     \
            return IJson( name );                                                                 \
        }  else if constexpr (ITraitUtil::is_std_vector_v< type >){                        \
            return WrapProcessWith< type >( name );                                         \
        }  else if constexpr ($HAS_CLASS_MEMBER_toJson< type >::value){                     \
            qDebug() << "call here";                                                       \
        }                                                                             \
        return nullptr;                                                                  \
    }

#endif
