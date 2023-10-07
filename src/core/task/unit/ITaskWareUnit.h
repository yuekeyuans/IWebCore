#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskManage.h"
#include "core/task/ITaskPreProcessor.h"

$PackageWebCoreBegin

template<class T, bool enabled = true>
class ITaskWareUnit : public ITaskWare
{
    $AsTaskUnit(ITaskWareUnit)
    Q_DISABLE_COPY_MOVE(ITaskWareUnit)
protected:
    ITaskWareUnit() = default;
    virtual ~ITaskWareUnit() = default;
};

$UseTaskUnit(ITaskWareUnit){
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            ITaskManage::instance()->addTaskWare(T::instance());
        });
    }
}

$PackageWebCoreEnd
