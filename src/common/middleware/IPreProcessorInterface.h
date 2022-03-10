#pragma once

#include "base/IHeaderUtil.h"
#include "common/middleware/IProcessorWare.h"
#include "controller/IControllerManage.h"
#include "task/IMiddleWareTaskUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IPreProcessorInterface : public IProcessorWare, public IMiddleWareTaskUnit<T, enabled>
{
public:
    IPreProcessorInterface() = default;

    virtual bool match(IRequest& request, IResponse& response) override = 0;
    virtual bool action(IRequest& request, IResponse& response) override = 0;

    virtual void task() final;
};


template<typename T, bool enabled>
void IPreProcessorInterface<T, enabled>::task()
{
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            auto inst = T::instance();
            IControllerManage::registerPreProcessor(inst);
        });
    }
}

$PackageWebCoreEnd
