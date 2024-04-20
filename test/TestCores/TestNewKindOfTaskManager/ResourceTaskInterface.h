#pragma once

#include <IWebCore>
#include "core/task/ITaskWare.h"
#include "core/task/ITaskManage.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/unit/ISingletonUnit.h"

template<typename T, bool enabled=true>
class ResourceTaskInterface : public ITaskWareUnit<T, true>, public ISingletonUnit<T>
{
public:
    ResourceTaskInterface() = default;
};
