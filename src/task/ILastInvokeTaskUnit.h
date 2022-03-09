#pragma once

#include "base/IHeaderUtil.h"
#include "task/ITaskManage.h"
#include "task/ITaskWare.h"

$PackageWebCoreBegin

template<typename T, bool enabled>
class ILastInvokeTaskUnit : public ITaskWare
{
    $UseWare
public:
    ILastInvokeTaskUnit() = default;
    virtual QString taskFinishTip();
    virtual void task() = 0;

private:
    class ILastInvokeTaskUnitPrivate{
    public:
        ILastInvokeTaskUnitPrivate();
    };

    static ILastInvokeTaskUnitPrivate m_private;
    virtual ILastInvokeTaskUnitPrivate* ILastInvokeTaskUnitTouch(){
        return & m_private;
    }
};

template<typename T, bool enabled>
typename ILastInvokeTaskUnit<T, enabled>::ILastInvokeTaskUnitPrivate
    ILastInvokeTaskUnit<T, enabled>::m_private;

template<typename T, bool enabled>
ILastInvokeTaskUnit<T, enabled>::ILastInvokeTaskUnitPrivate::ILastInvokeTaskUnitPrivate(){
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            ITaskManage::registerFirstInvoker([](){
                auto inst = T::instance();
                inst->task();
                inst->printTips();
            });
        });
    }
}

$PackageWebCoreEnd
