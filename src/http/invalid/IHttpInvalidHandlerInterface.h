#pragma once

#include "core/task/unit/ITaskWareUnit.h"
#include "http/IHttpTaskCatagory.h"

template<typename T, bool enabled>
class IHttpInvalidHandlerInterface : public ITaskWareUnit<T, enabled>
{
public:
    IHttpInvalidHandlerInterface();

public:
    virtual void $catagory() const final;
    virtual void $task() final;
};


template<typename T, bool enabled>
void IHttpInvalidHandlerInterface<T, enabled>::$catagory()
{
    return IHttpTaskCatagory::CATAGORY;
}
