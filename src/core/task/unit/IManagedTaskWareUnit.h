#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskManage.h"
#include "core/task/ITaskPreProcessor.h"

$PackageWebCoreBegin

template<class T, bool enabled = true>
class IManagedTaskWareUnit : public ITaskWare
{
    $AsTaskUnit(IManagedTaskWareUnit)
    Q_DISABLE_COPY_MOVE(IManagedTaskWareUnit)
protected:
    IManagedTaskWareUnit() = default;
    virtual ~IManagedTaskWareUnit() = default;
};

$UseTaskUnit(IManagedTaskWareUnit){
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            ITaskManage::instance()->addTaskWare(T::instance());
        });
    }
}

$PackageWebCoreEnd
