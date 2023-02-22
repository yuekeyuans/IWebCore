#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskManage.h"
#include "core/unit/IRegisterInstanceUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IContextTaskInterface : public ITaskWare, public IRegisterInstanceUnit<T, enabled>
{
public:
    IContextTaskInterface() = default;

public:
    virtual void task() = 0;

    virtual QString name() const override;
    virtual QStringList orders() const override;
    virtual QString catagory()  const final;
    virtual void registerToBase() final;
};

template<typename T, bool enabled>
QString IContextTaskInterface<T, enabled>::name() const
{
    return IMetaUtil::getMetaClassName(T::staticMetaObject);
}

template<typename T, bool enabled>
QStringList IContextTaskInterface<T, enabled>::orders() const
{
    return {};
}

template<typename T, bool enabled>
QString IContextTaskInterface<T, enabled>::catagory() const
{
    return "StartUp";
}

template<typename T, bool enabled>
void IContextTaskInterface<T, enabled>::registerToBase()
{
    ITaskManage::instance()->addTaskWare(T::instance());
}

$PackageWebCoreEnd
