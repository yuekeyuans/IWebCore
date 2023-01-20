#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/ITaskInfo.h"

$PackageWebCoreBegin

class ITaskCatagory
{
public:
    ITaskCatagory();
    QString getName() const;

private:
    void addTaskInfo(const ITaskInfo&);

private:
    QString m_name;
    QList<ITaskInfo> m_taskInfos;
};

$PackageWebCoreEnd
