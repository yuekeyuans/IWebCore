#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/test/ITestPreProcessor.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskManage.h"
#include "core/test/ITestManage.h"
#include "core/unit/IRegisterInstanceUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled =true>
class ITestTaskInterface: public ITaskWare , public IRegisterInstanceUnit<T, enabled>, public QObject
{
public:
    ITestTaskInterface() = default;

public:
    virtual QString name() const override;
    virtual QString catagory() const override;
    virtual void registerToBase() final;
    virtual void task() final;
};

template<typename T, bool enabled>
QString ITestTaskInterface<T, enabled>::name() const
{
    return IMetaUtil::getMetaClassName(T::staticMetaObject);
}

template<typename T, bool enabled>
QString ITestTaskInterface<T, enabled>::catagory() const
{
    return "Test";
}

template<typename T, bool enabled>
void ITestTaskInterface<T, enabled>::registerToBase()
{
    ITaskManage::instance()->addTaskWare(T::instance());
}

template<typename T, bool enabled>
void ITestTaskInterface<T, enabled>::task()
{
    ITestManage::registerTestClass(T::instance());
}

$PackageWebCoreEnd
