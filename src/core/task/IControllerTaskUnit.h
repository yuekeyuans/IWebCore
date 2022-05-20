#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/task/ITaskManage.h"
#include "core/task/ITaskWare.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IControllerTaskUnit : public ITaskWare
{
    $UseWare
public:
    IControllerTaskUnit() = default;
    virtual QString taskFinishTip() final;
    virtual void task() override = 0;

private:
    class IControllerTaskUnitPrivate{
    public:
        IControllerTaskUnitPrivate();
    };

    static IControllerTaskUnitPrivate m_private;
    virtual IControllerTaskUnitPrivate* IControllerTaskUnitPrivateTouch(){
        return &m_private;
    }
};


template<typename T, bool enabled>
typename IControllerTaskUnit<T, enabled>::IControllerTaskUnitPrivate
    IControllerTaskUnit<T, enabled>::m_private;

template<typename T, bool enabled>
QString IControllerTaskUnit<T, enabled>::taskFinishTip(){
    QString name = IMetaUtil::getMetaClassName(T::staticMetaObject);
    QString tip = QString("Controller ").append(name).append(" registered");
    return tip;
}

template<typename T, bool enabled>
IControllerTaskUnit<T, enabled>::IControllerTaskUnitPrivate::IControllerTaskUnitPrivate(){
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            ITaskManage::registerController([](){
                auto inst = T::instance();
                inst->task();
                inst->printTips();
            });
        });
    }
}

$PackageWebCoreEnd
