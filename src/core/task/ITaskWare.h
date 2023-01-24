#pragma once

#include "base/IHeaderUtil.h"
#include "core/unit/IOrderUnit.h"

$PackageWebCoreBegin

class ITaskWare : public IOrderUnit
{
public:
    ITaskWare() = default;
    virtual ~ITaskWare() = default;

public:
    virtual QString name() const = 0;
    virtual void task() = 0;
    virtual QString catagory() const = 0;
    virtual bool isTaskDefaultEnabled() const;
    bool isTaskEnabled() const;
};

$PackageWebCoreEnd
