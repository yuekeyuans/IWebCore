#include "IContextSystemVariableTask.h"
#include "core/config/IContextManage.h"
$PackageWebCoreBegin

QJsonValue IContextSystemVariableTask::getSystemConfig()
{
    return getSystemEnvironment();
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
