#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/test/ITestTaskInterface.h"
#include "core/test/IUnitTestManage.h"

$PackageWebCoreBegin

class IUnitTestTask : public ITestTaskInterface<IUnitTestTask>
{
public:
    IUnitTestTask() = default;
public:
    virtual void $task() final;
};

$PackageWebCoreEnd
