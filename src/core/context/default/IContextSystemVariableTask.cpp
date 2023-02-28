#include "IContextSystemVariableTask.h"
#include "core/context/IContextWritter.h"

$PackageWebCoreBegin

void IContextSystemVariableTask::task()
{
    loadSystemEnvironment();
}

void IContextSystemVariableTask::loadSystemEnvironment(){
    auto obj = getSystemEnvironment();
    IContextWritter::addSystemConfig(obj);
}

QJsonObject IContextSystemVariableTask::getSystemEnvironment(){
    QJsonObject obj;
    QStringList environment = QProcess::systemEnvironment();
    for(auto str : environment)
    {
        auto index = str.indexOf('=');
        auto key = str.left(index);
        auto value = str.mid(index +1 );
        obj[key] = value;
    }
    return obj;
}

$PackageWebCoreEnd
