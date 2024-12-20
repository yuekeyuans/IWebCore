﻿#pragma once

#include "core/util/ITraitUtil.h"
#include "core/util/IPreProcessorUtil.h"



#ifndef JSON_HEADER__PP
#define JSON_HEADER__PP

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
            } else if constexpr (ITraitUtil::has_class_member_toJson_v<T>){
                array.push_back( WrapBeanType( val ));
            }
        }

        return array;
    }
};


template<typename T>
IJson WrapProcessWith(const T& value){
    return ProcessWith<T>::toJson(value);
}

#define TO_JSON(type, name)                                                                   \
    type name;                                                                                \
    Q_INVOKABLE IJson name##_toJson () const                                                  \
    {                                                                                         \
        if constexpr (std::is_arithmetic_v< type >){                                          \
            return WrapPlainType(name);                                                       \
        } else if constexpr (std::is_same_v<std::string, type >){                             \
            return WrapPlainType(name);                                                       \
        }  else if constexpr (ITraitUtil::is_std_vector_v< type >){                           \
            return WrapProcessWith< type >( name );                                           \
        }  else if constexpr (ITraitUtil::has_class_member_toJson_v< type >){                 \
            return WrapBeanType(name);                                                        \
        }                                                                                     \
        return nullptr;                                                                       \
    }

#endif
