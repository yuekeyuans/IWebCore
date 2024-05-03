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

    // official Date format
    inline static constexpr char DateFormat[] = "yyyy-MM-dd";
    inline static constexpr char TimeFormat[] = "hh:mm:ss.zzz";
    inline static constexpr char DateTimeFormat[] = "yyyy-MM-dd hh:mm:ss.zzz";

    inline static constexpr char NewLine[] = "\r\n";

    inline static constexpr char InheritedMethod[] = "inherited method";
    inline static constexpr char UnImplimentedMethod[] = "unimplimented method, this will be implimented latter";
    inline static constexpr char UnVisibleMethod[] = "This method change visiblity to unvisible, if you see this, it means you call it illegally";
    inline static constexpr char UnCallableMethod[] = "This method can not be called anywhere.";

    inline static constexpr char ServerName[] = "IWebCore";
    inline static constexpr char MasterServer[] = "MasterServer";

    // length
    inline static constexpr int Request_Url_Max_Length = (2048 + 35);  // 2083
    inline static constexpr int Request_Header_Max_Length = (1024 * 8); // 8K
    inline static constexpr int Request_Body_Max_Length   = (1024 * 1024 * 4);  // 4M

    // session
    inline static constexpr double IDefaultOrderValue = 50;
}

$PackageWebCoreEnd
