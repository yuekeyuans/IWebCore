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

    extern const IString CommaSpace;
    extern const IString Semicolon;
    extern const IString NewLine;
    extern const IString Equal;
    extern const IString Empty;
    extern const IString Space;

    extern const IString Type;
    extern const IString Name;
    extern const IString True;
    extern const IString False;

    extern const std::vector<IString> EmptyVector;
    extern const std::vector<IString> StringTypes;
}

$PackageWebCoreEnd
