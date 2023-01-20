#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/ITaskNode.h"

$PackageWebCoreBegin

class ITaskManage;

class ITaskCatagory
{
public:
    ITaskCatagory() = default;
    virtual ~ITaskCatagory() = default;

public:
    virtual QString getName() {return "";};
    virtual QStringList getOrders(){ return {}; };

private:
    void addTaskInfo(const ITaskNode&);
    void execTaskNodes();

private:
    QList<ITaskNode> m_taskNodes;

private:
    friend class ITaskManage;
};

$PackageWebCoreEnd
