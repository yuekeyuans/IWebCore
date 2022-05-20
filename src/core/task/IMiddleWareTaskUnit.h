#pragma once

#include "ITaskWare.h"
#include "ITaskManage.h"
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

// TODO: 看一看这个可需要移动?
template<typename T, bool enabled=true>
class IMiddleWareTaskUnit : public ITaskWare
{
    $UseWare
public:
    IMiddleWareTaskUnit() = default;
    virtual QString taskFinishTip() final;
    virtual void task() override = 0;

private:
    class IMiddleWareTaskUnitPrivate{
    public:
        IMiddleWareTaskUnitPrivate();
    };

    static IMiddleWareTaskUnitPrivate m_private;
    virtual IMiddleWareTaskUnitPrivate* IMiddleWareTaskUnitPrivateTouch(){
        return &m_private;
    }
};


template<typename T, bool enabled>
typename IMiddleWareTaskUnit<T, enabled>::IMiddleWareTaskUnitPrivate
    IMiddleWareTaskUnit<T, enabled>::m_private;

template<typename T, bool enabled>
QString IMiddleWareTaskUnit<T, enabled>::taskFinishTip(){
    return "";  // TODO: 具体显示需要重载
}

template<typename T, bool enabled>
IMiddleWareTaskUnit<T, enabled>::IMiddleWareTaskUnitPrivate::IMiddleWareTaskUnitPrivate(){
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            ITaskManage::registerMiddleWare([](){
                auto inst = T::instance();
                inst->task();
                inst->printTips();
            });
        });
    }
}


$PackageWebCoreEnd
