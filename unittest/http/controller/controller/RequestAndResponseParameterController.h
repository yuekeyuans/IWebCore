#pragma once

#include "IWeb/IHttpControllerInterface"
/**
 * @brief The MethodParameterResolveTestController class
 * 这个类仅仅测试函数请求参数是否能够设置成功,不要求能够执行,
 * 也就是能够编译,运行不报错就可以
 */
class RequestAndResponseParameterController : public IHttpControllerInterface<RequestAndResponseParameterController>
{
    Q_GADGET
public:
    RequestAndResponseParameterController() = default;

//    $GetMapping(bareRequest)
//    QString bareRequest(IRequest request){
//        Q_UNUSED(bareRequest)
//        return "hello world";
//    }

    $GetMapping(request)
    QString request(IRequest& request){
        Q_UNUSED(request)
        return "hello world";
    }

    $GetMapping(constRequest)
    QString constRequest(const IRequest& request){
        Q_UNUSED(request)
        return "hello world";
    }

    $GetMapping(response)
    QString response(IResponse& request){
        Q_UNUSED(request)
        return "hello world";
    }

//    $GetMapping(bareResponse)
//    QString bareResponse(IResponse request){
//        Q_UNUSED(request)
//        return "hello world";
//    }

//    $GetMapping(constResponse)
//    QString constResponse(const IResponse& request){
//        Q_UNUSED(request)
//        return "hello world";
//    }

    $GetMapping(onlyResponse)
    void onlyResponse(IResponse& response){
        Q_UNUSED(response)
    }

    // decorators
//    $GetMapping(decoratorRequest)
    QString decoratorRequest(IRequest& $Path(request)){
        return {};
    }
};

