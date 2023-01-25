#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/task/ITaskManage.h"
#include "core/task/ITaskWare.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class ISessionTaskUnit : public ITaskWare
{
public:
    ISessionTaskUnit() = default;
    virtual ~ISessionTaskUnit() = default;

    virtual QString taskFinishTip() final;
    virtual void task() =0;

private:
    class ISessionTaskUnitPrivate{
    public:
        ISessionTaskUnitPrivate();
    };

    static ISessionTaskUnitPrivate m_private;
    virtual ISessionTaskUnitPrivate* ISessionTaskUnitPrivateTouch(){
        return &m_private;
    }
};

template<typename T, bool enabled>
typename ISessionTaskUnit<T, enabled>::ISessionTaskUnitPrivate
    ISessionTaskUnit<T,enabled>::m_private;

template<typename T, bool enabled>
QString ISessionTaskUnit<T, enabled>::taskFinishTip()
{
    QString name = IMetaUtil::getMetaClassName(T::staticMetaObject);
    QString tip = QString("Session Interface ").append(name).append(" registered");
    return tip;
}

template<typename T, bool enabled>
ISessionTaskUnit<T, enabled>::ISessionTaskUnitPrivate::ISessionTaskUnitPrivate()
{
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            ITaskManage::registerSessionInterface ([](){
                auto inst = T::instance();
                inst->task();
            });
        });
    }
}

$PackageWebCoreEnd
