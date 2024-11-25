#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/test/IUnitTestManage.h"
#include "core/test/IUnitTestCatagory.h"
#include "core/task/unit/ITaskWareUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IUnitTestInterface :  public ITaskWareUnit<T, IUnitTestCatagory, enabled>, public QObject, public ISingletonUnit<T>
{
public:
    IUnitTestInterface() = default;

public:
    virtual void $task() final;
};

template<typename T, bool enabled>
void IUnitTestInterface<T, enabled>::$task()
{
    IUnitTestManage::instance()->addTest(T::instance());
}

$PackageWebCoreEnd
