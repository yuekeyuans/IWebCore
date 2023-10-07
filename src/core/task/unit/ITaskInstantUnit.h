#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/ITaskPreProcessor.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class ITaskInstantUnit
{
    $AsTaskUnit(ITaskInstantUnit)
public:
    ITaskInstantUnit() = default;

public:
    virtual void task() = 0;
};

$UseTaskUnit(ITaskInstantUnit)
{
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, []{
            T{}.task();
        });
    }
}

$PackageWebCoreEnd
