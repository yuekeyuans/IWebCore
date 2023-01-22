﻿#pragma once

#include "base/IHeaderUtil.h"
#include "core/unit/IOrderUnit.h"

$PackageWebCoreBegin

class ITaskWare;
class ITaskManage;

class ITaskCatagory : public IOrderUnit
{
public:
    ITaskCatagory() = default;
    virtual ~ITaskCatagory() = default;

public:
    virtual QString name() const = 0;

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