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

    inline static const IString Comma = ": ";
    inline static const IString NewLine = "\r\n";
    inline static const IString Equal = "=";
    inline static const IString Empty {};
    inline static const std::vector<IString> EmptyVector {};
}

$PackageWebCoreEnd
