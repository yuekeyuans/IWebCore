#pragma once

#include "core/task/unit/ITaskWareUnit.h"
#include "http/IHttpTaskCatagory.h"
#include "http/IHttpManage.h"

$PackageWebCoreBegin

class IRequest;
class IHttpInvalidHandlerWare
{
public:
    virtual void handle(IRequest&) const = 0;
};

template<typename T, typename Invalid, bool enabled=true>
class IHttpInvalidHandlerInterface : public IHttpInvalidHandlerWare, public ITaskWareUnit<T, IHttpTaskCatagory, enabled>, public ISingletonUnit<T>
{
public:
    virtual double $order() const override;
    virtual void $task() final;
};

template<typename T, typename Invalid, bool enabled>
double IHttpInvalidHandlerInterface<T, Invalid, enabled>::$order() const
{
    return 10;
}

template<typename T, typename Invalid, bool enabled>
void IHttpInvalidHandlerInterface<T, Invalid, enabled>::$task()
{
    if constexpr (enabled){
        IHttpManage::instance()->registInvalidHandler(Invalid::CLASS_NAME, T::instance());
    }
}

$PackageWebCoreEnd
