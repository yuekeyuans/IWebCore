#pragma once

#include "core/task/ITaskManage.h"
#include "core/task/ITaskWare.h"
#include "core/base/IHeaderUtil.h"
#include "core/base/ITraitHelper.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IDirectTaskUnit : public ITaskWare
{
    $AsTaskUnit(IDirectTaskUnit)
public:
    IDirectTaskUnit() = default;

public:
    virtual void task() = 0;
};

$UseTaskUnit(IDirectTaskUnit)
{
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, []{
            T{}.task();
        });
    }
}

$PackageWebCoreEnd
