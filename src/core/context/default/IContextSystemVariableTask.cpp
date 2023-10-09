#include "IContextSystemVariableTask.h"
#include "core/context/IContextManage.h"
$PackageWebCoreBegin

void IContextSystemVariableTask::task()
{
    loadSystemEnvironment();
}

void IContextSystemVariableTask::loadSystemEnvironment(){
    auto obj = getSystemEnvironment();
    IContextManage::addConfig(obj, IContextManage::SystemContextGroup);
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
