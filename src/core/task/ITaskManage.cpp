#include "ITaskManage.h"

#include "core/configuration/IConfigurationManage.h"
#include "core/assert/IGlobalAssert.h"
#include "core/task/ITaskNode.h"

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

    inst->execTaskCatagories();
    inst->execTaskNodes();

    // clean the content
    inst->m_taskNodes.clear();
    inst->m_catagories.clear();
    inst->m_isTaskFinished = true;
}

void ITaskManage::addTaskNode(const ITaskNode &node)
{
    if(m_isTaskFinished){

    }

    m_taskNodes.append(node);
}

void ITaskManage::execTaskCatagories()
{
    QList<ITaskNode> cataNodes;
    for(const auto& node : m_taskNodes){
        if(node.mode == ITaskNode::Mode::Catagory){
            cataNodes.append(node);
        }
    }

    // TODO: here we sort cataNodes, temp skip this step

    for(auto node : cataNodes){
        node.function();
    }
}

void ITaskManage::execTaskNodes()
{
    for(const auto& node : m_taskNodes){
        if(node.mode == ITaskNode::Mode::Task){
            for(auto& cata : m_catagories){
                if(cata.getName() == node.catagory){
                    cata.addTaskInfo(node);
                    break;
                }
            }
        }
    }

    for(auto& node : m_catagories){
        node.execTaskNodes();
    }
}

$PackageWebCoreEnd
