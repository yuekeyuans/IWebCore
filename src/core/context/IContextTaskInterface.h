#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/task/unit/IManagedTaskWareUnit.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskManage.h"
#include "core/context/IContextPreProcessor.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IContextTaskInterface : public IManagedTaskWareUnit<T, enabled>
{
public:
    IContextTaskInterface() = default;

protected:
    virtual QString name() const override;
    virtual QString catagory() const final;
};

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
