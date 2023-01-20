#include "ITaskManage.h"

#include "core/configuration/IConfigurationManage.h"
#include "core/assert/IGlobalAssert.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskCatagory.h"

$PackageWebCoreBegin

$UseGlobalAssert()

void ITaskManage::run()
{
    QStringList arguments;
    run(arguments);
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

//    inst->execTaskCatagories();
    inst->execTaskNodes();

    // clean the content
    inst->m_taskWares.clear();
    inst->m_catagories.clear();
    inst->m_isTaskFinished = true;
}

void ITaskManage::addTaskWare(ITaskWare *node)
{
    if(m_isTaskFinished){

    }

    m_taskWares.append(node);
}

void ITaskManage::addTaskCatagory(ITaskCatagory *catagory)
{
    m_catagories.append(catagory);
}

void ITaskManage::execTaskNodes()
{
    for(const auto& node : m_taskWares){
        for(auto& cata : m_catagories){
            if(cata->getName() == node->catagory()){
                cata->addTask(node);
                break;
            }
        }
    }

    for(auto& node : m_catagories){
        node->execTaskNodes();
    }
}

$PackageWebCoreEnd
