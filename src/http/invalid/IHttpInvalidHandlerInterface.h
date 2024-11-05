#pragma once

#include "core/task/unit/ITaskWareUnit.h"

template<typename T, bool enabled>
class IHttpInvalidHandlerInterface : public ITaskWareUnit<T, enabled>
{
public:
    IHttpInvalidHandlerInterface();
};

