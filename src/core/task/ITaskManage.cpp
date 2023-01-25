#include "ITaskManage.h"

#include "core/configuration/IConfigurationManage.h"
#include "core/assert/IGlobalAssert.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskCatagory.h"

$PackageWebCoreBegin

$UseGlobalAssert()

void ITaskManage::run()
{
    auto inst = instance();
    inst->invokeTaskCatagories();

    inst->m_taskWares.clear();
    inst->m_catagories.clear();
    inst->m_isTaskFinished = true;
}

void ITaskManage::addTaskWare(ITaskWare *node)
{
    if(m_isTaskFinished){
        $GlobalAssert->fatal("TaskShouldNotBeRegistered");
    }

    m_taskWares.append(node);
}

void ITaskManage::addTaskCatagory(ITaskCatagory *catagory)
{
    m_catagories.append(catagory);
}

void ITaskManage::invokeTaskCatagories()
{
    checkCatagoryExceed();
    checkTaskExceed();

    mergetTasksToCatagores();
    execEachCatagory();
}

void ITaskManage::checkCatagoryExceed()
{
    for(const auto& cata : m_catagories){
        if(cata->order() < 0 || cata->order() > 100){
            IAssertInfo info;
            info.reason = QString("Catagory: ").append(cata->name());
            $GlobalAssert->warn("CatagoryRangeExceed", info);
        }
    }
}

void ITaskManage::checkTaskExceed()
{
    for(const auto& task : m_taskWares){
        if(task->order() < 0 || task->order() > 100){
            IAssertInfo info;
            info.reason = QString("Task: ").append(task->name());
            $GlobalAssert->warn("TaskRangeExceed", info);
        }
    }
}

void ITaskManage::mergetTasksToCatagores()
{
    IOrderUnit::sortUnit(m_catagories);

    QList<ITaskWare*> wares;
    for(auto task : m_taskWares){
        for(auto& cata : m_catagories){
            if(cata->name() == task->catagory()){
                cata->addTask(task);
                wares.append(task);
                break;
            }
        }
    }

    if(m_catagories.length() != m_taskWares.length()){
        for(auto task : wares){
            m_taskWares.removeOne(task);
        }

        for(auto task: m_taskWares){
            IAssertInfo info;
            info.reason = QString("Task: ").append(task->name()).append(" have wrong catagory that not exist: ").append(task->catagory());
            $GlobalAssert->warn("TaskWithErrorCatagory", info);
        }
    }
}

void ITaskManage::execEachCatagory()
{

    for(const auto& node : m_catagories){
        if(node->isCatagoryEnabled()){
            node->sortTask();
            node->printTaskInfo();
        }
    }

    for(auto& node : m_catagories){
        if(node->isCatagoryEnabled()){
            node->execTaskNodes();
        }
    }
}

$PackageWebCoreEnd
