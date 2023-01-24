#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/ITaskManage.h"
#include "core/task/ITaskCatagory.h"
#include "core/unit/IRegisterInstanceUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class ITaskCatagoryInterface : public ITaskCatagory, public IRegisterInstanceUnit<T, enabled>
{
    Q_DISABLE_COPY_MOVE(ITaskCatagoryInterface)
public:
    ITaskCatagoryInterface() = default;

public:
    virtual void registerToBase() final;
};

template<typename T, bool enabled>
void ITaskCatagoryInterface<T, enabled>::registerToBase(){
    ITaskManage::instance()->addTaskCatagory(T::instance());
}

$PackageWebCoreEnd
