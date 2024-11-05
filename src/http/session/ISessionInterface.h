#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "http/session/ISessionWare.h"
#include "http/IHttpControllerTaskCatagory.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class ISessionInterface : public ISessionWare, public ITaskWareUnit<T, enabled>
{
public:
    ISessionInterface() = default;

public:
    virtual double $order() const override;
    virtual const char* $catagory() const final;
    virtual void $task() final;
};

namespace ISessionInterfaceProxy
{
    void registerSession(ISessionWare*);
}

template<typename T, bool enabled>
double ISessionInterface<T, enabled>::$order() const
{
    return 49;
}

template<typename T, bool enabled>
const char* ISessionInterface<T, enabled>::$catagory() const
{
    return IHttpControllerTaskCatagory::CATAGORY;
}

template<typename T, bool enabled>
void ISessionInterface<T, enabled>::$task ()
{
    if constexpr (enabled){
        static std::once_flag flag;
        std::call_once(flag, [&](){
            ISessionInterfaceProxy::registerSession (T::instance());
        });
    }
}

//template<typename T, bool enabled>
//void ISessionInterface<T, enabled>::registerSession ()
//{
//    ISessionInterfaceProxy::registerSession (T::instance());
//}

$PackageWebCoreEnd
