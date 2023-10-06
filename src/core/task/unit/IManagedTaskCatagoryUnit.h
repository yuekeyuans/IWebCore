#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/ITaskCatagory.h"
#include "core/task/ITaskPreProcessor.h"

$PackageWebCoreBegin

template<class T, bool enabled = true>
class IManagedTaskCatagoryUnit : public ITaskCatagory
{
    Q_DISABLE_COPY_MOVE(IManagedTaskCatagoryUnit)
    $AsTaskUnit(IManagedTaskCatagoryUnit)
protected:
    IManagedTaskCatagoryUnit() = default;
    virtual ~IManagedTaskCatagoryUnit() = default;
};

$UseTaskUnit(IManagedTaskCatagoryUnit){
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            ITaskManage::instance()->addTaskCatagory(T::instance());
        });
    }
}

$PackageWebCoreEnd
