#include "ITaskWare.h"

$PackageWebCoreBegin

QString ITaskWare::taskFinishTip()
{
    return "";
}

void ITaskWare::printTips()
{
    QString tip = taskFinishTip();
    if(!tip.isEmpty()){
        qDebug().noquote() << QStringLiteral("[√]\t") << tip;
    }
}

$PackageWebCoreEnd
