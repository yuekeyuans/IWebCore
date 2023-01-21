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
    virtual QString name() const = 0;
    virtual QStringList orders() const;

private:
    void addTask(ITaskWare*);
    void execTaskNodes() const;
    void printTaskInfo() const;

private:
    QList<ITaskWare*> m_taskWares;

private:
    friend class ITaskManage;
};

$PackageWebCoreEnd
