#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/ITaskWare.h"
#include "core/test/ITestManage.h"

$PackageWebCoreBegin

template<typename T, bool enabled>
class ITestTaskUnit : public ITaskWare
{
public:
    ITestTaskUnit() = default;
    virtual ~ITestTaskUnit() = default;
    virtual void task() final{};

private:
    class ITestTaskUnitPrivate{
    public:
        ITestTaskUnitPrivate();
    };

    static ITestTaskUnitPrivate m_private;
    virtual ITestTaskUnitPrivate* ITestTaskUnitUnitPrivateTouch(){
        return &m_private;
    }
};

template<typename T, bool enabled>
typename ITestTaskUnit<T, enabled>::ITestTaskUnitPrivate
    ITestTaskUnit<T, enabled>::m_private;


template<typename T, bool enabled>
ITestTaskUnit<T, enabled>::ITestTaskUnitPrivate::ITestTaskUnitPrivate(){
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            ITestManage::registerTestClass(T::instance());
        });
    }
}

$PackageWebCoreEnd
