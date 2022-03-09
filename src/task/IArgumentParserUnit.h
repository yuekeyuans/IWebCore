#pragma once

#include "base/IHeaderUtil.h"
#include "common/support/IRegisterInstanceUnit.h"
#include "task/ITaskWare.h"
#include "task/ITaskManage.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IArgumentParserUnit : public ITaskWare
{
    $UseWare
public:
    using FunType = void(*)(const QStringList&);

public:
    IArgumentParserUnit() = default;
    virtual ~IArgumentParserUnit() = default;

    virtual void task(const QStringList& arguements) = 0;

private:
    virtual void task() final {};  // 禁用 无参 task，并重新构造一个 有参的 task

private:
    class IArgumentParserUnitPrivate{
    public:
        IArgumentParserUnitPrivate();
    };

    static IArgumentParserUnitPrivate m_private;
    virtual IArgumentParserUnitPrivate* IArgumentParserUnitPrivateTouch(){
        return &m_private;
    }
};

template<typename T, bool enabled>
typename IArgumentParserUnit<T, enabled>::IArgumentParserUnitPrivate
    IArgumentParserUnit<T, enabled>::m_private;

template<typename T, bool enabled>
IArgumentParserUnit<T, enabled>::IArgumentParserUnitPrivate::IArgumentParserUnitPrivate(){
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            ITaskManage::registerArgumentParser([](const QStringList& arguments){
                auto inst = T::instance();
                inst->task(arguments);
                inst->printTips();
            });
        });
    }
}

$PackageWebCoreEnd
