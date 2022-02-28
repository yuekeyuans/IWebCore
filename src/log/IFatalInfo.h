#pragma once

#include "ILogInfo.h"
$PackageWebCoreBegin

// TODO: 所有的log 组件都要重新实现一遍， 参考 QMessageLogger
struct IFatalInfo : public ILogInfo
{
public:
    void fatal();
    virtual IFatalInfo &setExtra(const QString &key, const QString &value) final;
    virtual IFatalInfo &setMessage(const QString &message) final;

private:
    virtual void log() final {};
};


$PackageWebCoreEnd


#define $Fatal() \
    []()->IFatalInfo { \
        IFatalInfo info;    \
        info.time = QDateTime::currentDateTime();   \
        info.lineNumber = __LINE__; \
        info.fileName = __FILE__;   \
        info.functionName = __FUNCTION__;   \
        return info; \
    }()
