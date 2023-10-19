#include "ITaskCatagory.h"
#include "core/task/ITaskWare.h"
#include "core/context/IContextManage.h"

$PackageWebCoreBegin

bool ITaskCatagory::isCatagoryDefaultEnabled() const
{
    return true;
}

bool ITaskCatagory::isCatagoryEnabled() const
{
    bool ok;
    auto path = QString("CATAGORY_ENABLE_STATE_").append(name());
    auto value = IContextManage::instance()->getConfig(path, &ok);
    if(!ok){
        return isCatagoryDefaultEnabled();
    }

    return value.toBool();
}

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
        if(!node->isTaskEnabled()){
            continue;
        }
        node->task();
    }
}

void ITaskCatagory::printTaskInfo() const
{
    bool ok;
    ok = IContextManage::instance()->getConfig("SYSTEM_ENABLE_TASK_OUTPUT", &ok).toBool() && ok;
    if(ok){
        qDebug() << endl << "Catagory: " << name() << ", order: " << order();
    }

    for(const auto& node : m_taskWares){
        if(!node->isTaskEnabled()){
            continue;
        }

        if(ok){
            QString tip = QString("`").append(node->name()).append("` registered.");
            if(!tip.isEmpty()){
                qDebug().noquote() << "    " << QStringLiteral("[√]  ") << tip << " order: " << node->order();
            }
        }
    }
}

$PackageWebCoreEnd
