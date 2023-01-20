#include "ITaskCatagory.h"
#include "core/task/ITaskWare.h"

$PackageWebCoreBegin

void ITaskCatagory::addTask(ITaskWare *ware)
{
    m_taskWares.append(ware);
}

void ITaskCatagory::execTaskNodes()
{
    // TODO: first is sort node, skip this and this will be complete latter.
    for(auto& node : m_taskWares){
        node->task();
    }
}

$PackageWebCoreEnd
