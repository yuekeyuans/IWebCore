#include "ITaskCatagory.h"

$PackageWebCoreBegin

ITaskCatagory::ITaskCatagory()
{
}

QString ITaskCatagory::getName() const
{
    return m_name;
}

void ITaskCatagory::addTaskInfo(const ITaskInfo & info)
{
    m_taskInfos.append(info);
}

$PackageWebCoreEnd
