#pragma once

#include "base/IHeaderUtil.h"
#include "common/middleware/IInterceptorWare.h"
#include "controller/IControllerManage.h"
#include "task/IMiddleWareTaskUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
    class IPostInterceptorInterface : public IInterceptorWare, public IMiddleWareTaskUnit<T, enabled>
{
public:
    IPostInterceptorInterface() = default;

    virtual bool match(IRequest& request, IResponse& response) override = 0;
    virtual bool action(IRequest& request, IResponse& response) override = 0;

    virtual void task() final;
};

template<typename T, bool enabled>
void IPostInterceptorInterface<T, enabled>::task()
{
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            auto inst = T::instance();
            IControllerManage::registerInterceptor(inst);
        });
    }
}

$PackageWebCoreEnd
