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
                    && sizeof(&T::toVariantMap) != 0
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
}

$PackageWebCoreEnd
