#include "IHttpControllerAction.h"
#include "http/controller/detail/IHttpControllerParameter.h"
#include "http/server/ITcpConnection.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/net/impl/IRequestRaw.h"

$PackageWebCoreBegin


void IHttpControllerAction::invoke(IRequest &request) const
{
    auto params = createParams(request);
    if(request.isValid()){
        auto index = methodNode.metaMethod.methodIndex();
        auto enclosingObject = methodNode.metaMethod.enclosingMetaObject();
        enclosingObject->static_metacall(QMetaObject::InvokeMetaMethod, index, params.data());
        if(request.isValid()){
            methodNode.returnNode.resolveValue(request, params[0]);
        }
    }

    destroyParams(params);
    request.doWrite();
}

//void IHttpControllerAction::invoke(IRequest &request) const
//{
//    IHttpControllerParameter::ParamType params;
//    auto ok = IHttpControllerParameter::createArguments(methodNode, params, request);
//    if(!ok){
//        IHttpControllerParameter::destroyArguments(methodNode, params);
//        return;
//    }

//    auto index = methodNode.metaMethod.methodIndex();
//    auto enclosingObject = methodNode.metaMethod.enclosingMetaObject();
//    enclosingObject->static_metacall(QMetaObject::InvokeMetaMethod, index, params);
//    if(!request.isValid()){
//        return;
//    }

//    IResponse response(&request);
//    IHttpControllerParameter::resolveReturnValue(response, methodNode, params);
//    if(request.isValid()){
//        IHttpControllerParameter::destroyArguments(methodNode, params);
//    }

//    request.doWrite();
//}

IHttpControllerAction::ParamType IHttpControllerAction::createParams(IRequest& request) const
{
    ParamType params;
    params[0] = methodNode.returnNode.create(request);
    int len = methodNode.argumentNodes.length();
    for(int i=0; i<len; i++){
        params[i+1] = methodNode.argumentNodes[i].create(request);
        if(!request.isValid()){
            break;
        }
    }
    return params;
}

void IHttpControllerAction::destroyParams(IHttpControllerAction::ParamType params) const
{
    methodNode.returnNode.destroy(params[0]);
    int len = methodNode.argumentNodes.length();
    for(int i=0; i<len; i++){
        if(params[i]){
            methodNode.argumentNodes[i].destory(params[i+1]);
        }
    }
}

$PackageWebCoreEnd
