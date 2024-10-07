#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/task/default/IEndupTaskInterface.h"
$PackageWebCoreBegin

template<typename T, typename TestManage>
class ITestTaskBaseInterface : public IEndupTaskInterface<T>
{
public:
    ITestTaskBaseInterface() = default;

public:
    virtual double $order() const final;
    virtual void $task() override;
};

template<typename T, typename TestManage>
double ITestTaskBaseInterface<T, TestManage>::$order() const
{
    return 100;
}

template<typename T, typename TestManage>
void ITestTaskBaseInterface<T, TestManage>::$task()
{
    TestManage::instance()->invokeTests();
}

$PackageWebCoreEnd
