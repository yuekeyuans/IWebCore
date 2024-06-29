#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskPreProcessor.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class ITaskInstantUnit
{
//    $AsTaskUnit(ITaskInstantUnit)
private:    \
    class ITaskInstantUnitInitPrivate{ \
    public: \
        ITaskInstantUnitInitPrivate(); \
    };  \
    static ITaskInstantUnitInitPrivate m_private;  \
    virtual void* ITaskInstantUnitInitPrivateTouch(){  \
        return &m_private;  \
    }

public:
    ITaskInstantUnit() = default;

public:
    virtual void task() = 0;
};

//$UseTaskUnit(ITaskInstantUnit)
template<typename T, bool enabled>
typename ITaskInstantUnit <T, enabled>::
         ITaskInstantUnitInitPrivate \
         ITaskInstantUnit <T, enabled>::m_private;    \
template<typename T, bool enabled>  \
         ITaskInstantUnit<T, enabled>:: \
         ITaskInstantUnitInitPrivate ::     \
         ITaskInstantUnitInitPrivate ()
{
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, []{
            T{}.task();
        });
    }
}

$PackageWebCoreEnd
