#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

namespace ITraitUtil
{
    template <typename T, typename = void>
    struct is_gadget : std::false_type {};

    template <typename T>
    struct is_gadget<T, std::void_t<decltype(T::staticMetaObject)>> : std::true_type {};

    template<typename T>
    constexpr bool is_gadget_v = is_gadget<T>::value;

    template<typename T, typename = void>
    struct is_bean
    {
        enum { value = false};
    };

    template<typename T>
    struct is_bean<T, std::void_t<typename T::QtGadgetHelper>>
    {
        enum {
            value = std::is_class<T>::value == true
                    && is_gadget_v<T>
                    && (sizeof(&T::toJson) != 0)
                    && sizeof(&T::toVariantMap) != 0
        };
    };

    template<typename T>
    bool is_bean_v = is_bean<T>::value;
}

$PackageWebCoreEnd
