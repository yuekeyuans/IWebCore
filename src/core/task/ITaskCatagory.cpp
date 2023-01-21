#include "ITaskCatagory.h"
#include "core/task/ITaskWare.h"

$PackageWebCoreBegin

void ITaskCatagory::addTask(ITaskWare *ware)
{
    m_taskWares.append(ware);
}

void ITaskCatagory::execTaskNodes() const
{
    // TODO: first is sort node, skip this and this will be complete latter.
    for(auto& node : m_taskWares){
        node->task();
    }
}

void ITaskCatagory::printTaskInfo() const
{
    qDebug() << endl << "Catagory: " << name();

    for(const auto& node : m_taskWares){
        QString tip = QString("`").append(node->name()).append("` registered");
        if(!tip.isEmpty()){
            qDebug().noquote() << "    " << QStringLiteral("[√]  ") << tip;
        }
    }
}

$PackageWebCoreEnd
