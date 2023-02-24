#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/unit/IRegisterInstanceUnit.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskManage.h"
#include "core/context/IContextPreProcessor.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IContextTaskInterface : public ITaskWare, public IRegisterInstanceUnit<T, enabled>
{
public:
    IContextTaskInterface() = default;

public:
    virtual void registerToBase() final;

protected:
    virtual QString name() const override;
    virtual QString catagory() const final;
};

template<typename T, bool enabled>
void IContextTaskInterface<T, enabled>::registerToBase()
{
    ITaskManage::instance()->addTaskWare(T::instance());
}

template<typename T, bool enabled>
QString IContextTaskInterface<T, enabled>::name() const
{
    return IMetaUtil::getMetaClassName(T::staticMetaObject);
}

template<typename T, bool enabled>
QString IContextTaskInterface<T, enabled>::catagory() const
{
    return "Context";
}


$PackageWebCoreEnd
