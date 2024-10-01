#pragma once

#include "core/util/IHeaderUtil.h"
#include <type_traits>

$PackageWebCoreBegin

#define PP_CLASS_HAS_MEMBER(member)                                                                      \
    template <typename T, typename = void>                                                               \
    struct has_class_member_##member : std::false_type {};                                               \
    template <typename T>                                                                                \
    struct has_class_member_##member<T, std::void_t<decltype(&T::member)>> : std::true_type {};          \
    template<typename T>                                                                                 \
    inline constexpr bool has_class_member_##member##_v = has_class_member_##member <T>::value;

namespace ITraitUtil
{   
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


    // std::map<std::string, T>
    template<typename T>
    struct is_std_string_map : std::false_type {};
    template<typename Value, typename Compare, typename Alloc>
    struct is_std_string_map<std::map<std::string, Value, Compare, Alloc>> : std::true_type {};
    template<typename T>
    inline constexpr bool is_std_string_map_v = is_std_string_map<T>::value;


    // QMap<QString, T>
    template<typename T>
    struct is_q_string_map : std::false_type {};
    template<typename Value>
    struct is_q_string_map<QMap<QString, Value>> : std::true_type {};
    template<typename T>
    inline constexpr bool is_q_string_map_v = is_q_string_map<T>::value;

    // has member json
    PP_CLASS_HAS_MEMBER(toJson)
}

$PackageWebCoreEnd
