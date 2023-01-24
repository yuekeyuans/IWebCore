#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/test/ITestPreProcessor.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskManage.h"
#include "core/test/ITestManage.h"
#include "core/unit/IRegisterInstanceUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled =true>
class ITestInterface: public ITaskWare , public IRegisterInstanceUnit<T, enabled>, public QObject
{
public:
    ITestInterface() = default;

public:
    virtual QString name() const override;
    virtual QString catagory() const override;
    virtual void registerToBase() final;
    virtual void task() final;
};

template<typename T, bool enabled>
QString ITestInterface<T, enabled>::name() const
{
    return IMetaUtil::getMetaClassName(T::staticMetaObject);
}

template<typename T, bool enabled>
QString ITestInterface<T, enabled>::catagory() const
{
    return "Test";
}

template<typename T, bool enabled>
void ITestInterface<T, enabled>::registerToBase()
{
    ITaskManage::instance()->addTaskWare(T::instance());
}

template<typename T, bool enabled>
void ITestInterface<T, enabled>::task()
{
    ITestManage::registerTestClass(T::instance());
}

$PackageWebCoreEnd
