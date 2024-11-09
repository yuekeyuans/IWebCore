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
    IHttpControllerParameter::ParamType params;
    auto ok = IHttpControllerParameter::createArguments(methodNode, params, request);
    if(!ok){
        IHttpControllerParameter::destroyArguments(methodNode, params);
        return;
    }

    auto index = methodNode.metaMethod.methodIndex();
    auto enclosingObject = methodNode.metaMethod.enclosingMetaObject();
    enclosingObject->static_metacall(QMetaObject::InvokeMetaMethod, index, params);
    if(!request.isValid()){
        return;
    }

    IResponse response(&request);
    IHttpControllerParameter::resolveReturnValue(response, methodNode, params);
    if(request.isValid()){
        IHttpControllerParameter::destroyArguments(methodNode, params);
    }

    request.doWrite();
}

$PackageWebCoreEnd
