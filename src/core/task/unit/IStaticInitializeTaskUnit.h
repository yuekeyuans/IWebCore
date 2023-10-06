#pragma once

#include "core/task/ITaskManage.h"
#include "core/task/ITaskWare.h"
#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IStaticInitializeTaskUnit : public ITaskWare
{
    $AsTaskRegistray(IStaticInitializeTaskUnit)
public:
    IStaticInitializeTaskUnit() = default;

public:
    virtual void task() = 0;
};

$UseTaskRegistray(IStaticInitializeTaskUnit)

$PackageWebCoreEnd
