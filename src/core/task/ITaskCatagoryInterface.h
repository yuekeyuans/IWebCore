#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/ITaskManage.h"
#include "core/task/ITaskCatagory.h"
#include "core/task/unit/ITaskCatagoryUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class ITaskCatagoryInterface : public ITaskCatagoryUnit<T, enabled>
{
    Q_DISABLE_COPY_MOVE(ITaskCatagoryInterface)
public:
    ITaskCatagoryInterface() = default;
};

$PackageWebCoreEnd
