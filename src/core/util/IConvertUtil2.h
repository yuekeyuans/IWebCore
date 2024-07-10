#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/base/IResult.h"
#include "core/base/IStringView.h"

$PackageWebCoreBegin

namespace IConvertUtil2
{
//    template<typename Ret, typename Arg>
//    std::enable_if_t<!std::is_arithmetic_v<Arg>, IResult<Ret>>
//    convertTo(const Arg&);

//    template<typename Ret, typename Arg>
//    std::enable_if_t<std::is_arithmetic_v<Arg>, IResult<Ret>>
//    convertTo(Arg);

    template<typename Ret, typename Arg>
    IResult<Ret> convertTo(const Arg&);

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
