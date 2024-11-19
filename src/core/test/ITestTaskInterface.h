#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/test/ITestCatagory.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class ITestTaskInterface : public ITaskWareUnit<T, ITestCatagory, true>
{
public:
    ITestTaskInterface() = default;
public:
    virtual void $task() = 0;
};

$PackageWebCoreEnd
