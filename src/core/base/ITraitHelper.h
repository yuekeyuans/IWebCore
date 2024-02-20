#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

namespace ITraitHelper
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

    template<typename T>
    struct IsChar { enum {value = false}; };
    template<> struct IsChar<char> { enum {value = true}; };
    template<> struct IsChar<uchar> { enum {value = true}; };

    template<typename T>
    struct IsNumber{ enum { value = false}; };
    template<> struct IsNumber<signed char> { enum {value = true}; };       // NOTE: 根据 c++ 安全编码， signed/unsigned char 是数字类型， char 本身作为字符类型。
    template<> struct IsNumber<unsigned char> { enum {value = true}; };
    template<> struct IsNumber<short> { enum {value = true}; };
    template<> struct IsNumber<ushort> { enum {value = true}; };
    template<> struct IsNumber<int> { enum {value = true}; };
    template<> struct IsNumber<uint> { enum {value = true}; };
    template<> struct IsNumber<long> { enum {value = true}; };
    template<> struct IsNumber<ulong> { enum {value = true}; };
    template<> struct IsNumber<qlonglong> { enum {value = true}; };
    template<> struct IsNumber<qulonglong> { enum {value = true}; };
    template<> struct IsNumber<float> { enum {value = true}; };
    template<> struct IsNumber<double> { enum {value = true}; };
}

$PackageWebCoreEnd
