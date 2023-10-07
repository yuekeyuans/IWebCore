#pragma once

#include <IWebCore>
#include "core/task/ITaskWare.h"
#include "core/task/ITaskManage.h"
#include "core/task/unit/ITaskWareUnit.h"

template<typename T, bool enabled=true>
class ResourceTaskInterface : public ITaskWareUnit<T, true>
{
public:
    ResourceTaskInterface() = default;
};
