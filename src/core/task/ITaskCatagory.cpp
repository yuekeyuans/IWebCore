#include "ITaskCatagory.h"

$PackageWebCoreBegin

void ITaskCatagory::addTaskInfo(const ITaskNode& info)
{
    m_taskNodes.append(info);
}

void ITaskCatagory::execTaskNodes()
{
    // TODO: first is sort node, skip this and this will be complete latter.

    for(auto& node : m_taskNodes){
        node.function();
    }
}

$PackageWebCoreEnd
