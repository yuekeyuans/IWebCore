#pragma once

#include "IHeaderUtil.h"

$PackageWebCoreBegin

namespace IConstantUtil
{
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

    static constexpr char ServerName[] = "IWebCore";

    //! char[] of new line.
    static constexpr char NewLine[] = "\r\n";

    static constexpr char InheritedMethod[] = "inherited method";
    static constexpr char UnImplimentedMethod[] = "unimplimented method, this will be implimented latter";
    static constexpr char UnVisibleMethod[] = "This method change visiblity to unvisible, if you see this, it means you call it illegally";
    static constexpr char UnCallableMethod[] = "This method can not be called anywhere.";

    static constexpr char MasterServer[] = "MasterServer";

    // length;
    static constexpr int Request_Url_Max_Length = (2048 + 35);  // 2083
    static constexpr int Request_Header_Max_Length = (1024 * 8); // 8K
    static constexpr int Request_Body_Max_Length   = (1024 * 1024 * 4);  // 4M

    // session
    static constexpr int Session_Expiration = 30;

    // configuration  暂时的
    static constexpr bool IServerNameMiddleWareEnabeld = true;
    static constexpr bool ICookiePluginEnabled = true;
    static constexpr bool ICorsPluginEnabled = true;


    void deprecateWarning();
}

inline void IConstantUtil::deprecateWarning(){
    Q_UNUSED(DebugMode)
    Q_UNUSED(ReleaseMode)

    Q_UNUSED(ServerName)
    Q_UNUSED(NewLine)
    Q_UNUSED(InheritedMethod)
    Q_UNUSED(UnImplimentedMethod)
    Q_UNUSED(UnVisibleMethod)

    Q_UNUSED(UnCallableMethod)
    Q_UNUSED(MasterServer)
    Q_UNUSED(Request_Url_Max_Length)
    Q_UNUSED(Request_Header_Max_Length)
    Q_UNUSED(Request_Body_Max_Length)

    Q_UNUSED(Session_Expiration)

    Q_UNUSED(IServerNameMiddleWareEnabeld)
    Q_UNUSED(ICookiePluginEnabled)
    Q_UNUSED(ICorsPluginEnabled)

    qFatal("this function is used for deprecate warnings above, do not call this");
}

$PackageWebCoreEnd
