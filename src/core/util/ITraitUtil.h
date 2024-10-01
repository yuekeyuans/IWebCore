#pragma once

#include "core/util/IHeaderUtil.h"
#include <type_traits>

$PackageWebCoreBegin

namespace ITraitUtil
{
//    template<typename Type, typename ... Args>
//    struct isContain : std::bool_constant<(std::is_same_v<Type, Args>) || ...>{};

    template <typename T, typename = void>
    struct isGadget : std::false_type {};

    template <typename T>
    struct isGadget<T, std::void_t<decltype(T::staticMetaObject)>> : std::true_type {};

    template<typename T>
    constexpr bool is_gadget_v = isGadget<T>::value;

    template<typename T, typename = void>
    struct isBean
    {
        enum { value = false};
    };

    template<typename T>
    struct isBean<T, std::void_t<typename T::QtGadgetHelper>>
    {
        enum {
            value = std::is_class<T>::value == true
                    && is_gadget_v<T>
                    && (sizeof(&T::toJson) != 0)
//                    && sizeof(&T::toVariantMap) != 0
        };
    };

    // bean type
    template<typename T>
    inline constexpr bool isBeanType = isBean<T>::value;

    template<typename Type, typename ... Args>
    inline constexpr bool isContain_v = isContain<Type, Args...>::value;

    // 基础类型，数值类型 + const char*, IStringView
    template<typename Arg>
    inline constexpr bool isBasicType = (isContain_v<Arg, const char*, IStringView>) || std::is_arithmetic_v<Arg>;


    // std::vector
    template<typename T>
    struct is_std_vector : std::false_type {};

    template<typename T, typename Alloc>
    struct is_std_vector<std::vector<T, Alloc>> : std::true_type {};

    template<typename T>
    inline constexpr bool is_std_vector_v = is_std_vector<T>::value;


    // QVector
    template<typename T>
    struct is_q_vector : std::false_type {};

    template<typename T>
    struct is_q_vector<QVector<T>> : std::true_type {};

    template<typename T>
    inline constexpr bool is_q_vector_v = is_q_vector<T>::value;


    // std::map
    template<typename T>
    struct is_std_map : std::false_type {};

    template<typename Key, typename Value, typename Compare, typename Alloc>
    struct is_std_map<std::map<Key, Value, Compare, Alloc>> : std::true_type {};

    template<typename T>
    inline constexpr bool is_std_map_v = is_std_map<T>::value;


    // QMap
    template<typename T>
    struct is_q_map : std::false_type {};

    template<typename Key, typename Value>
    struct is_q_map<QMap<Key, Value>> : std::true_type {};

    template<typename T>
    inline constexpr bool is_q_map_v = is_q_map<T>::value;
}

$PackageWebCoreEnd
