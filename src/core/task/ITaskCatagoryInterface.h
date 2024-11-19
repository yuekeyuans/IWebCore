#pragma once

#include "core/unit/ISingletonUnit.h"
#include "core/task/ITaskManage.h"
#include "core/task/ITaskCatagory.h"
#include "core/task/unit/ITaskCatagoryUnit.h"
#include "core/unit/IClassNameUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class ITaskCatagoryInterface : public ITaskCatagoryUnit<T, enabled>, public ISingletonUnit<T>, public IClassNameUnit<T>
{
public:
    ITaskCatagoryInterface() = default;

public:
    virtual const QString& $catagory() const final;
};

template<typename T, bool enabled>
const QString& ITaskCatagoryInterface<T, enabled>::$catagory() const
{
    return T::CLASS_NAME;
}

$PackageWebCoreEnd
