#pragma once

#include "core/task/ITaskManage.h"
#include "core/task/ITaskWare.h"
#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IStaticInitializeTaskUnit : public ITaskWare
{
    $AsRegistray(IStaticInitializeTaskUnit)
public:
    IStaticInitializeTaskUnit() = default;

public:
    virtual void task() = 0;
};

$UseRegistray(IStaticInitializeTaskUnit)
{
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, []{
            T inst;
            inst.task();
        });
    }
}

$PackageWebCoreEnd
