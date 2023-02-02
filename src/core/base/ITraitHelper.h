#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

namespace ITraitHelper
{
    template<typename T, typename Enable = void>
    struct IsBean {
        enum { value = false};
    };

    template<typename T>
    struct IsBean<T, typename T::QtGadgetHelper>
    {
        enum {
            value = std::is_class<T>::value == true
                    && sizeof(&T::qt_check_for_QGADGET_macro) != 0
                    && sizeof(&T::toJson) != 0
                    && sizeof(&T::toVariantMap) != 0
        };
    };

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
};

$PackageWebCoreEnd
