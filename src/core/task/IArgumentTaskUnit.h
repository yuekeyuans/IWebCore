#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskManage.h"
#include "core/unit/IRegisterInstanceUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IArgumentTaskUnit : public ITaskWare
{
    $UseWare
public:
    using FunType = void(*)(const QStringList&);

public:
    IArgumentTaskUnit() = default;
    virtual ~IArgumentTaskUnit() = default;

    virtual void task(const QStringList& arguements) = 0;

private:
    virtual void task() final {};  // 禁用 无参 task，并重新构造一个 有参的 task

private:
    class IArgumentTaskUnitPrivate{
    public:
        IArgumentTaskUnitPrivate();
    };

    static IArgumentTaskUnitPrivate m_private;
    virtual IArgumentTaskUnitPrivate* IArgumentTaskUnitPrivateTouch(){
        return &m_private;
    }
};

template<typename T, bool enabled>
typename IArgumentTaskUnit<T, enabled>::IArgumentTaskUnitPrivate
    IArgumentTaskUnit<T, enabled>::m_private;

template<typename T, bool enabled>
IArgumentTaskUnit<T, enabled>::IArgumentTaskUnitPrivate::IArgumentTaskUnitPrivate()
{
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            ITaskManage::registerArgumentTask([](const QStringList& arguments){
                auto inst = T::instance();
                inst->task(arguments);
                inst->printTips();
            });
        });
    }
}

$PackageWebCoreEnd
