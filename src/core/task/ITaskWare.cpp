#include "ITaskWare.h"

$PackageWebCoreBegin

QString ITaskWare::taskFinishTip()
{
    return "";
}

ITaskNode::Mode ITaskWare::mode()
{
    return ITaskNode::Mode::Task;
}

void ITaskWare::printTips()
{
    QString tip = taskFinishTip();
    if(!tip.isEmpty()){
        qDebug().noquote() << QStringLiteral("[√]\t") << tip;
    }
}

ITaskNode ITaskWare::toTaskNode()
{
    ITaskNode node;
    node.mode = mode();
    node.name = name();
    node.orders = orders();
    node.catagory = catagory();
    node.function = [=](){
        return std::bind(std::mem_fn(&ITaskWare::task), this);
    };

    return node;
}

$PackageWebCoreEnd
