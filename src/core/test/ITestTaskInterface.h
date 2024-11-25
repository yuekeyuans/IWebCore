#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/test/IUnitTestCatagory.h"
#include "core/task/default/IEndUpTaskCatagory.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class ITestTaskInterface : public ITaskWareUnit<T, IEndupTaskCatagory, true>
{
public:
    ITestTaskInterface() = default;
public:
    virtual void $task() = 0;
};

$PackageWebCoreEnd
