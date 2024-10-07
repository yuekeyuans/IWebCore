#include "ITaskCatagory.h"
#include "core/task/ITaskWare.h"
#include "core/config/IContextImport.h"

$PackageWebCoreBegin

bool ITaskCatagory::$isCatagoryDefaultEnabled() const
{
    return true;
}

QString ITaskCatagory::$name() const
{
    return $catagory();
}

bool ITaskCatagory::isCatagoryEnabled() const
{
    auto path = QString("/CATAGORY_ENABLE_STATE_").append($name());
    $ContextBool value{path.toStdString(), $isCatagoryDefaultEnabled()};
    return *value;
}

void ITaskCatagory::addTask(ITaskWare *ware)
{
    m_taskWares.append(ware);
}

void ITaskCatagory::sortTask()
{
    IOrderUnitUtil::sortUnit(m_taskWares);
}

void ITaskCatagory::execTaskNodes() const
{
    for(auto& node : m_taskWares){
        if(!node->isTaskEnabled()){
            continue;
        }
        node->$task();
    }
}

void ITaskCatagory::printTaskInfo() const
{
    static $ContextBool value{"/SYSTEM_ENABLE_TASK_OUTPUT", false};
    if(!value.value()){
        return;
    }

    qDebug() << Qt::endl << "Catagory: " << $name() << ", order: " << $order();
    for(const auto& node : m_taskWares){
        if(node->isTaskEnabled()){
            qDebug().noquote() << QStringLiteral("\t[√]  ")
                               << QString("`").append(node->$name()).append("` registered.")
                               << " order: " << node->$order();
        }
    }
}

$PackageWebCoreEnd
