#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/base/IResult.h"
#include "core/base/IStringView.h"
#include "core/util/ITraitUtil.h"

$PackageWebCoreBegin

namespace IConvertUtil2
{
    template<typename Ret, typename Arg>
    std::enable_if_t<!ITraitUtil::isBasicType<Arg>,  IResult<Ret>> to(const Arg& arg);

    template<typename Ret, typename Arg>
    IResult<Ret> to(const QList<Arg>& arg);

    template<typename Ret, typename Arg>
    IResult<Ret> to(const QMap<QString, Arg>& arg);

#define PP_COMMON_CONVERT(Type)     \
    template<typename Ret>  \
    IResult<Ret> convertTo(Type);

    PP_COMMON_CONVERT(bool)
    PP_COMMON_CONVERT(char)
    PP_COMMON_CONVERT(signed char)
    PP_COMMON_CONVERT(unsigned char)
    PP_COMMON_CONVERT(signed short)
    PP_COMMON_CONVERT(unsigned short)
    PP_COMMON_CONVERT(signed int)
    PP_COMMON_CONVERT(unsigned int)
    PP_COMMON_CONVERT(signed long)
    PP_COMMON_CONVERT(unsigned long)
    PP_COMMON_CONVERT(signed long long)
    PP_COMMON_CONVERT(unsigned long long)
    PP_COMMON_CONVERT(float)
    PP_COMMON_CONVERT(double)
    PP_COMMON_CONVERT(const char*)
    PP_COMMON_CONVERT(IStringView)
}

$PackageWebCoreEnd
