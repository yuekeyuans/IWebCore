#pragma once

#include "ILogInfo.h"

$PackageWebCoreBegin
struct IErrorMessage : public ILogInfo
{
};

$PackageWebCoreEnd

#define $Error() \
    []()->IErrorMessage { \
        IErrorMessage info;    \
        info.time = QDateTime::currentDateTime();   \
        info.lineNumber = __LINE__; \
        info.fileName = __FILE__;   \
        info.functionName = __FUNCTION__;   \
        return info; \
    }()
