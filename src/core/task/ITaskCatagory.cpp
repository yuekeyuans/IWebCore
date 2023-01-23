#include "ITaskCatagory.h"
#include "core/task/ITaskWare.h"

$PackageWebCoreBegin

void ITaskCatagory::addTask(ITaskWare *ware)
{
    m_taskWares.append(ware);
}

void ITaskCatagory::sortTask()
{
    IOrderUnit::sortUnit(m_taskWares);
}

void ITaskCatagory::execTaskNodes() const
{
    for(auto& node : m_taskWares){
        node->task();
    }
}

void ITaskCatagory::printTaskInfo() const
{
    qDebug() << endl << "Catagory: " << name() << ", order: " << order();

    for(const auto& node : m_taskWares){
        QString tip = QString("`").append(node->name()).append("` registered.");
        if(!tip.isEmpty()){
            qDebug().noquote() << "    " << QStringLiteral("[√]  ") << tip << " order: " << node->order();
        }
    }
}

$PackageWebCoreEnd
