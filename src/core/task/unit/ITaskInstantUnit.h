#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskPreProcessor.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class ITaskInstantUnit
{
    $AsTaskUnit(ITaskInstantUnit)
public:
    ITaskInstantUnit() = default;

protected:
    virtual void task() = 0;
};

$UseTaskUnit(ITaskInstantUnit)
{
    if constexpr (enabled){
        static std::once_flag flag;
        std::call_once(flag, []{
            T value{};
            static_cast<ITaskInstantUnit*>(&value)->task();
        });
    }
}

$PackageWebCoreEnd
