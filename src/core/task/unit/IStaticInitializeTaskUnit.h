#pragma once

#include "core/task/ITaskManage.h"
#include "core/task/ITaskWare.h"
#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IStaticInitializeTaskUnit : public ITaskWare
{
    $DeclareInit(IStaticInitializeTaskUnit)
public:
    IStaticInitializeTaskUnit() = default;

public:
    virtual void task() = 0;
};

$UseInit(IStaticInitializeTaskUnit)
{
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, []{
            static auto inst = new T();
            inst->task();
        });
    }
}

$PackageWebCoreEnd
