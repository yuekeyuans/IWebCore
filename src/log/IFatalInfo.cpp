#include "IFatalInfo.h"
#include "base/IConstantUtil.h"

$PackageWebCoreBegin

void IFatalInfo::fatal()
{
    fileName = fileName.split("\\").last();
    QString place = QString("at\t [file: %1] [function: %2] [line: %3]").arg(fileName).arg(functionName).arg(lineNumber).toUtf8();

    QString info;
    info.append("msg:\t").append(message).append('\n');
    info.append(place).append('\n');
    if(extras.size() != 0){
        info.append("extra info:\n");
        for(auto key : extras.keys()){
            info.append('\t').append(key).append(':').append(extras[key]).append('\n');
        }
    }
    qFatal(info.toUtf8());
}

IFatalInfo &IFatalInfo::setExtra(const QString &key, const QString &value)
{
    ILogInfo::setExtra(key, value);
    return *this;
}

IFatalInfo &IFatalInfo::setMessage(const QString &message)
{
    ILogInfo::setMessage(message);
    return *this;
}

$PackageWebCoreEnd
