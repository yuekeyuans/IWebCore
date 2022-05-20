#pragma once

#include "base/IHeaderUtil.h"
#include "web/middleware/IProcessorWare.h"
#include "controller/IControllerManage.h"
#include "core/task/IMiddleWareTaskUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IPostProcessorInterface : public IProcessorWare, public IMiddleWareTaskUnit<T, enabled>
{
public:
    using IMiddleWare::operator();

public:
    IPostProcessorInterface() = default;

    virtual bool match(IRequest& request, IResponse& response) override = 0;
    virtual bool action(IRequest& request, IResponse& response) override = 0;

public:
    virtual QString name() override = 0;
    virtual void task() final;
};


template<typename T, bool enabled>
void IPostProcessorInterface<T, enabled>::task()
{
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            auto inst = T::instance();
            IControllerManage::registerPostProcessor(inst);
        });
    }
}

$PackageWebCoreEnd
