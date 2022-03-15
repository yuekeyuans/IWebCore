#pragma once

#include "IHeaderUtil.h"

$PackageWebCoreBegin

/*! @namespace IConstantUtil
 * @brief list some often used constants.
 *
 **/
namespace IConstantUtil
{
    // debugMode;
#ifdef QT_DEBUG
    static constexpr bool DebugMode = true;
    static constexpr bool ReleaseMode = false;
#else
    static constexpr bool DebugMode = true;
    static constexpr bool ReleaseMode = false;
#endif

    //! official Date format
    static const QString DateFormat = "yyyy-MM-dd";
    static const QString TimeFormat = "hh:mm:ss.zzz";
    static const QString DateTimeFormat = "yyyy-MM-dd hh:mm:ss.zzz";

    //! char[] of new line.
    static const char* const NewLine = "\r\n";

    static const char* const InheritedMethod = "inherited method";
    static const char* const UnImplimentedMethod = "unimplimented method, this will be implimented latter";

    // length;
    static constexpr int Request_Url_Max_Length = (2048 + 35);  // 2083
    static constexpr int Request_Header_Max_Length = (1024 * 8); // 8K
    static constexpr int Request_Body_Max_Length   = (1024 * 1024 * 4);  // 4M

    // configuration  暂时的
    static constexpr bool IServerNameMiddleWareEnabeld = true;
    static constexpr bool ICookiePluginEnabled = true;
    static constexpr bool ICorsPluginEnabled = true;

};

$PackageWebCoreEnd
