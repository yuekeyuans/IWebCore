#include "ITaskManage.h"

#include "core/config/IContextImport.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskCatagory.h"
#include "core/abort/IAbortInterface.h"

$PackageWebCoreBegin

class ITaskManageAbort : public IAbortInterface<ITaskManageAbort>
{
    $AsAbort(
        TaskShouldNotBeRegistered,
        CatagoryRangeExceed,
        TaskRangeExceed,
        TaskWithErrorCatagory
    )
protected:
    virtual QMap<int, QString> abortDescription() const final{
        return {
            {TaskShouldNotBeRegistered, "task can not be registered when the task run finished"},
            {CatagoryRangeExceed, "catagory range ought to be in 0 and 100"},
            {TaskRangeExceed, "catagory range ought to be in 0 and 100"},
            {TaskWithErrorCatagory, "this task`s catagory does not exist, please check your code"}
        };
    }
};

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
        ITaskManageAbort::abortTaskShouldNotBeRegistered($ISourceLocation);
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
        if(cata->$order() < 0 || cata->$order() > 100){
            ITaskManageAbort::abortCatagoryRangeExceed(QString("Catagory: ").append(cata->$name()), $ISourceLocation);
        }
    }
}

void ITaskManage::checkTaskExceed()
{
    for(const auto& task : m_taskWares){
        if(task->$order() < 0 || task->$order() > 100){
            ITaskManageAbort::abortTaskRangeExceed(QString("Task: ").append(task->$name()), $ISourceLocation);
        }
    }
}

void ITaskManage::mergetTasksToCatagores()
{
    IOrderUnitUtil::sortUnit(m_catagories);

    QList<ITaskWare*> wares;
    for(auto task : m_taskWares){
        for(auto& cata : m_catagories){
            if(strcmp(cata->$catagory(), task->$catagory()) == 0){
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
            ITaskManageAbort::abortTaskWithErrorCatagory(QString("Task: ").append(task->$name()).append(" have wrong catagory that not exist: ").append(task->$catagory()), $ISourceLocation);
        }
    }
}

void ITaskManage::execEachCatagory()
{
    static $ContextBool printable{"/SYSTEM_ENABLE_TASK_OUTPUT", false};
    for(const auto& node : m_catagories){
        if(node->isCatagoryEnabled()){
            node->sortTask();
            if(printable.value()){
               node->printTaskInfo();
            }
            node->execTaskNodes();
        }
    }
}

$PackageWebCoreEnd
