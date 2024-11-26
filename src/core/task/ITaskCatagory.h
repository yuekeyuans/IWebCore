#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/IOrderUnit.h"

$PackageWebCoreBegin

class ITaskWare;
class ITaskManage;

class ITaskCatagory : public IOrderUnit
{
    friend class ITaskManage;
public:
    ITaskCatagory() = default;
    virtual ~ITaskCatagory() = default;

public:
    virtual const std::string& $name() const final;
    virtual const std::string& $catagory() const = 0;
    virtual bool $isCatagoryDefaultEnabled() const;

private:
    bool isCatagoryEnabled() const;
    void addTask(ITaskWare*);
    void sortTask();
    void execTaskNodes() const;
    void printTaskInfo() const;

private:
    QList<ITaskWare*> m_taskWares;
};

$PackageWebCoreEnd
