#pragma once

#include "core/task/ITaskManage.h"
#include "core/task/ITaskWare.h"
#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IStaticInitializeTaskUnit : public ITaskWare
{
public:
    IStaticInitializeTaskUnit() = default;


    virtual void task() = 0;

private:
    class IStaticInitializeTaskUnitPrivate{
    public:
        IStaticInitializeTaskUnitPrivate();
    };

    static IStaticInitializeTaskUnitPrivate m_private;
    virtual void* IStaticInitializeTaskUnitPrivateTouch(){
        return &m_private;
    }
};

template<typename T, bool enabled>
typename IStaticInitializeTaskUnit<T, enabled>::IStaticInitializeTaskUnitPrivate
    IStaticInitializeTaskUnit<T, enabled>::m_private;

template<typename T, bool enabled>
IStaticInitializeTaskUnit<T, enabled>::IStaticInitializeTaskUnitPrivate::IStaticInitializeTaskUnitPrivate(){
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, []{
            static auto inst = new T();
            inst->task();
//            inst->printTips();
        });
    }
}

$PackageWebCoreEnd
