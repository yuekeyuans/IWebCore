#include "ITaskManage.h"

#include "core/configuration/IConfigurationManage.h"
#include "core/assert/IGlobalAssert.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskCatagory.h"

$PackageWebCoreBegin

$UseGlobalAssert()

void ITaskManage::run()
{
    run({});
}

void ITaskManage::run(int argc, char **argv)
{
    QStringList arguments;
    for(int i=0; i<argc; i++){
        arguments << QString(argv[i]);
    }

    run(arguments);
}

void ITaskManage::run(const QStringList& arguments)
{
    auto inst = instance();
    inst->m_arguments = arguments;

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
    m_catagories = IOrderUnit::sortUnit(m_catagories);

    for(const auto& node : m_taskWares){
        for(auto& cata : m_catagories){
            if(cata->name() == node->catagory()){
                cata->addTask(node);
                break;
            }
        }
    }

    for(const auto& node : m_catagories){
        node->sortTask();
        node->printTaskInfo();
    }

    for(auto& node : m_catagories){
        node->execTaskNodes();
    }
}

$PackageWebCoreEnd
