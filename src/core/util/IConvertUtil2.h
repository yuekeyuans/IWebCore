#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/base/IResult.h"

$PackageWebCoreBegin

namespace IConvertUtil2{

    template<typename Ret, typename Arg>
    std::enable_if_t<!std::is_arithmetic_v<Arg>, IResult<Ret>>
    convertTo(const Arg&);

    template<typename Ret, typename Arg>
    std::enable_if_t<std::is_arithmetic_v<Arg>, IResult<Ret>>
    convertTo(Arg);

    template<typename Ret>
    IResult<Ret> convertTo(const char*);

}

$PackageWebCoreEnd
