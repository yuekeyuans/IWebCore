#pragma once

#include "log/ILogInfo.h"

$PackageWebCoreBegin

struct IDebugInfo : public ILogInfo
{

};

$PackageWebCoreEnd

#define $Debug() \
    []()->IErrorInfo { \
        IDebugInfo info;    \
        info.time = QDateTime::currentDateTime();   \
        info.lineNumber = __LINE__; \
        info.fileName = __FILE__;   \
        info.functionName = __FUNCTION__;   \
        return info; \
    }()

