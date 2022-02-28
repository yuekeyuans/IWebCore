#include "ILogInfo.h"

$PackageWebCoreBegin

void ILogInfo::log()
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
    qDebug().noquote().nospace() << info.toUtf8();
}

ILogInfo &ILogInfo::setExtra(const QString &key, const QString &value)
{
    extras[key] = value;
    return *this;
}

ILogInfo &ILogInfo::setMessage(const QString &message)
{
    this->message = message;
    return *this;
}

$PackageWebCoreEnd
