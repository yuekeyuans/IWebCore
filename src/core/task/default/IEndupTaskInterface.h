#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/task/ITaskManage.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/task/default/IEndupTaskCatagory.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IEndupTaskInterface : public ITaskWareUnit<T, enabled>, public ISingletonUnit<T>
{
public:
    IEndupTaskInterface() = default;

public:
    virtual void $task() = 0;

protected:
    virtual const QString& $catagory() const final;
};

template<typename T, bool enabled>
const QString& IEndupTaskInterface<T, enabled>::$catagory() const
{
    return IEndupTaskCatagory::CATAGORY;
}

$PackageWebCoreEnd
