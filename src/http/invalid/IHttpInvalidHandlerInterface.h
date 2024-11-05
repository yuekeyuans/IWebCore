#pragma once

#include "core/task/unit/ITaskWareUnit.h"
#include "http/IHttpTaskCatagory.h"

template<typename T, bool enabled>
class IHttpInvalidHandlerInterface : public ITaskWareUnit<T, IHttpTaskCatagory, enabled>
{
public:
    IHttpInvalidHandlerInterface();

public:
    virtual void $task() final;
};

