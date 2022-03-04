#pragma once

#include "base/IHeaderUtil.h"
#include "common/task/ITaskManage.h"
#include "common/task/ITaskWare.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IConfigurationTaskUnit : ITaskWare
{
    $UseWare
public:
    IConfigurationTaskUnit() = default;
    virtual void task() =0;

private:
    class IConfigurationTaskUnitPrivate{
    public:
        IConfigurationTaskUnitPrivate();
    };

    static IConfigurationTaskUnitPrivate m_instance;
    virtual IConfigurationTaskUnitPrivate* IConfigurationTaskUnitPrivateTouch(){
        return &m_instance;
    }
};

template<typename T, bool enabled>
typename IConfigurationTaskUnit<T, enabled>::IConfigurationTaskUnitPrivate
    IConfigurationTaskUnit<T, enabled>::m_instance;

template<typename T, bool enabled>
IConfigurationTaskUnit<T, enabled>::IConfigurationTaskUnitPrivate::IConfigurationTaskUnitPrivate(){
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            ITaskManage::registerConfigrator([](){
                auto inst = T::instance();
                inst->task();
                inst->printTips();
            });
        });
    }
}

$PackageWebCoreEnd
