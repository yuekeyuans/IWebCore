#pragma once

#include "ILogInfo.h"

$PackageWebCoreBegin

struct IWarnInfo : public ILogInfo
{
};

$PackageWebCoreEnd

#define $Warn() \
    []()->IWarnInfo { \
        IWarnInfo info;    \
        info.time = QDateTime::currentDateTime();   \
        info.lineNumber = __LINE__; \
        info.fileName = __FILE__;   \
        info.functionName = __FUNCTION__;   \
        return info; \
    }()
