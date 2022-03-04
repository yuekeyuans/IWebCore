#pragma once

#include "base/IHeaderUtil.h"
#include "common/task/ITaskManage.h"
#include "common/task/ITaskWare.h"

$PackageWebCoreBegin

template<typename T, bool enabled>
class IFirstInvokeTaskUnit : public ITaskWare
{
    $UseWare
public:
    IFirstInvokeTaskUnit() = default;
    virtual void task() = 0;

private:
    class IFirstInvokeTaskUnitPrivate{
    public:
        IFirstInvokeTaskUnitPrivate();
    };

    static IFirstInvokeTaskUnitPrivate m_private;
    virtual IFirstInvokeTaskUnitPrivate* IFirstInvokeTaskUnitTouch(){
        return & m_private;
    }
};

template<typename T, bool enabled>
typename IFirstInvokeTaskUnit<T, enabled>::IFirstInvokeTaskUnitPrivate
    IFirstInvokeTaskUnit<T, enabled>::m_private;

template<typename T, bool enabled>
IFirstInvokeTaskUnit<T, enabled>::IFirstInvokeTaskUnitPrivate::IFirstInvokeTaskUnitPrivate(){
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            ITaskManage::registerLastInvoker([](){
                auto inst = T::instance();
                inst->task();
                inst->printTips();
            });
        });
    }
}

$PackageWebCoreEnd
