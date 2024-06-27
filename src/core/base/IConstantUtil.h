#pragma once

#include "IHeaderUtil.h"

$PackageWebCoreBegin

namespace IConstantUtil
{
#ifdef QT_DEBUG
    inline static constexpr bool DebugMode = true;
    inline static constexpr bool ReleaseMode = false;
#else
    inline static constexpr bool DebugMode = false;
    inline static constexpr bool ReleaseMode = true;
#endif

    inline static constexpr char DateFormat[] = "yyyy-MM-dd";
    inline static constexpr char TimeFormat[] = "hh:mm:ss.zzz";
    inline static constexpr char DateTimeFormat[] = "yyyy-MM-dd hh:mm:ss.zzz";

    inline static constexpr char UnImplimentedMethod[] = "unimplimented method, this will be implimented latter";
}

$PackageWebCoreEnd
