#pragma once

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
    virtual const std::string& $name() const = 0;
    virtual void $task() = 0;
    virtual const std::string& $catagory() const = 0;
    virtual bool $isTaskDefaultEnabled() const;

private:
    bool isTaskEnabled() const;
};

$PackageWebCoreEnd
