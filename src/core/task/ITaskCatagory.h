#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class ITaskWare;
class ITaskManage;

class ITaskCatagory
{
public:
    ITaskCatagory() = default;
    virtual ~ITaskCatagory() = default;

public:
    virtual QString getName() = 0;
    virtual QStringList getOrders(){ return {}; };

private:
    void addTask(ITaskWare*);
    void execTaskNodes();

private:
    QList<ITaskWare*> m_taskWares;

private:
    friend class ITaskManage;
};

$PackageWebCoreEnd
