#pragma once

#include "ITaskWare.h"
#include "ITaskManage.h"
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

// 主要是 用于 配置环境完成后的初始化

template<typename T, bool enabled=true>
class IInitializationTaskUnit : public ITaskWare
{
    $UseWare
protected:
    IInitializationTaskUnit() = default;

public:
    virtual void task() = 0;

private:
    class ITaskInitializerUnitPrivate{
    public:
        ITaskInitializerUnitPrivate();
    };

    static ITaskInitializerUnitPrivate m_ITaskInitializerUnitPrivate;
    virtual void* ITaskInitializerUnitPrivateTouch(){
        return &m_ITaskInitializerUnitPrivate;
    }
};

template<typename T, bool enabled>
typename IInitializationTaskUnit<T, enabled>::ITaskInitializerUnitPrivate
    IInitializationTaskUnit<T, enabled>::m_ITaskInitializerUnitPrivate;

template<typename T, bool enabled>
IInitializationTaskUnit<T, enabled>::ITaskInitializerUnitPrivate::ITaskInitializerUnitPrivate(){
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            ITaskManage::registerInitializer([](){
                auto instance = T::instance();
                instance->task();
                instance->printTips();
            });
        });
    }
}

$PackageWebCoreEnd
