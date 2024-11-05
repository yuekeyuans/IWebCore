#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/test/ITestManageBaseInterface.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/test/ITestCatagory.h"

$PackageWebCoreBegin

template<typename T, typename Manage, bool enabled =true>
class ITestBaseInterface : public ITaskWareUnit<T, enabled>, public QObject, public ISingletonUnit<T>
{
public:
    ITestBaseInterface() = default;

public:
    virtual const QString& $catagory() const override;
    virtual void $task() final;
};

template<typename T, typename Manage, bool enabled>
const QString& ITestBaseInterface<T, Manage, enabled>::$catagory() const
{
    return ITestCatagory::CATAGORY;
}

template<typename T, typename Manage, bool enabled>
void ITestBaseInterface<T, Manage, enabled>::$task()
{
    Manage::instance()->addTest(T::instance());
}

$PackageWebCoreEnd
