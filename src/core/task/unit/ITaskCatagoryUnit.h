#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskCatagory.h"
#include "core/task/ITaskPreProcessor.h"

$PackageWebCoreBegin

template<class T, bool enabled = true>
class ITaskCatagoryUnit : public ITaskCatagory
{
    Q_DISABLE_COPY_MOVE(ITaskCatagoryUnit)
    $AsTaskUnit(ITaskCatagoryUnit)
protected:
    ITaskCatagoryUnit() = default;
    virtual ~ITaskCatagoryUnit() = default;
};

$UseTaskUnit(ITaskCatagoryUnit){
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            ITaskManage::instance()->addTaskCatagory(T::instance());
        });
    }
}

$PackageWebCoreEnd
