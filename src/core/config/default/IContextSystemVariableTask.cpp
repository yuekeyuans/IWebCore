#include "IContextSystemVariableTask.h"
#include "core/config/IContextManage.h"
$PackageWebCoreBegin

IJson IContextSystemVariableTask::config()
{
    return getSystemEnvironment();
}

IJson IContextSystemVariableTask::getSystemEnvironment(){
    IJson obj = IJson::object();
    QStringList environment = QProcess::systemEnvironment();
    for(auto str : environment)
    {
        auto index = str.indexOf('=');
        auto key = str.left(index);
        auto value = str.mid(index +1 );
        obj[key.toStdString()] = value.toStdString();
    }
    return obj;
}

$PackageWebCoreEnd
