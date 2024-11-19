#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/unit/ISingletonUnit.h"
#include "core/task/default/IInitializationTaskCatagory.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IInitializationTaskInterface : public ITaskWareUnit<T, IInitializationTaskCatagory, enabled>, public ISingletonUnit<T>
{
public:
    IInitializationTaskInterface() = default;

public:
    virtual void $task() = 0;
};

$PackageWebCoreEnd
