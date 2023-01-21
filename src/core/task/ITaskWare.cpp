#include "ITaskWare.h"

$PackageWebCoreBegin

QStringList ITaskWare::orders()
{
    return {};
}

void ITaskWare::printTips()
{
    QString tip = QString("`").append(name()).append("` in catagory `").append(catagory()).append("` finished");
    if(!tip.isEmpty()){
        qDebug().noquote() << QStringLiteral("[√]  ") << tip;
    }
}

$PackageWebCoreEnd
