//#pragma once

//#include "core/base/IHeaderUtil.h"
//#include "core/task/unit/IMiddleWareTaskUnit.h"
//#include "http/controller/IControllerManage.h"
//#include "http/middleware/IInterceptorWare.h"

//$PackageWebCoreBegin

//template<typename T, bool enabled=true>
//class IPostInterceptorInterface : public IInterceptorWare, public IMiddleWareTaskUnit<T, enabled>
//{
//public:
//    using IMiddleWare::operator();

//public:
//    IPostInterceptorInterface() = default;

//    virtual QString name() override = 0;
//    virtual bool match(IRequest& request, IResponse& response) override = 0;
//    virtual bool action(IRequest& request, IResponse& response) override = 0;

//    virtual void task() final;
//};


//template<typename T, bool enabled>
//void IPostInterceptorInterface<T, enabled>::task()
//{
//    if(enabled){
//        static std::once_flag flag;
//        std::call_once(flag, [](){
//            auto inst = T::instance();
//            IControllerManage::registerPostInterceptor(inst);
//        });
//    }
//}

//$PackageWebCoreEnd
