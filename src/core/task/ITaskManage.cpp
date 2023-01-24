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
    inst->execTaskNodes();

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

void ITaskManage::execTaskNodes()
{
    checkCatagoryExceed();
    checkTaskExceed();

    IOrderUnit::sortUnit(m_catagories);

    for(const auto& node : m_taskWares){
        for(auto& cata : m_catagories){
            if(cata->name() == node->catagory()){
                cata->addTask(node);
                break;
            }
        }
    }

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

$PackageWebCoreEnd
