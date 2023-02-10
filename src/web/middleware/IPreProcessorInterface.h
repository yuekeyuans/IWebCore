//#pragma once

//#include "core/base/IHeaderUtil.h"
//#include "core/task/unit/IMiddleWareTaskUnit.h"
//#include "web/middleware/IProcessorWare.h"
//#include "web/controller/IControllerManage.h"

//$PackageWebCoreBegin

//template<typename T, bool enabled=true>
//class IPreProcessorInterface : public IProcessorWare, public IMiddleWareTaskUnit<T, enabled>
//{
//public:
//    using IMiddleWare::operator();

//public:
//    IPreProcessorInterface() = default;

//    virtual bool match(IRequest& request, IResponse& response) override = 0;
//    virtual bool action(IRequest& request, IResponse& response) override = 0;

//public:
//    virtual QString name() override = 0;
//    virtual void task() final;
//};


//template<typename T, bool enabled>
//void IPreProcessorInterface<T, enabled>::task()
//{
//    if(enabled){
//        static std::once_flag flag;
//        std::call_once(flag, [](){
//            auto inst = T::instance();
//            IControllerManage::registerPreProcessor(inst);
//        });
//    }
//}

//$PackageWebCoreEnd
