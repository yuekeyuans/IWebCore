﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/IOrderUnit.h"

$PackageWebCoreBegin

class ITaskCatagory;
class ITaskWare : public IOrderUnit
{
    friend class ITaskCatagory;
public:
    ITaskWare() = default;
    virtual ~ITaskWare() = default;

public:
    virtual QString $name() const = 0;
    virtual void $task() = 0;
    virtual const char* $catagory() const = 0;
    virtual bool $isTaskDefaultEnabled() const;

private:
    bool isTaskEnabled() const;
};

$PackageWebCoreEnd
