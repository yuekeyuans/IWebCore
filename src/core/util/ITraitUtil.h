#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin
$IPackageBegin(ITraitUtil)

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

#define PP_CLASS_HAS_MEMBER(member)                                                                      \
    template <typename T, typename = void>                                                               \
    struct has_class_member_##member : std::false_type {};                                               \
    template <typename T>                                                                                \
    struct has_class_member_##member<T, std::void_t<decltype(&T::member)>> : std::true_type {};          \
    template<typename T>                                                                                 \
    inline constexpr bool has_class_member_##member##_v = has_class_member_##member <T>::value;

    PP_CLASS_HAS_MEMBER(toJson)
    PP_CLASS_HAS_MEMBER(fromJson)
#undef PP_CLASS_HAS_MEMBER

$IPackageEnd(ITraitUtil)
$PackageWebCoreEnd

