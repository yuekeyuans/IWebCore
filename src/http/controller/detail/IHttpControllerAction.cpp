#include "IHttpControllerAction.h"
#include "http/controller/detail/IHttpControllerParameter.h"
#include "http/server/ITcpConnection.h"

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
    if(!request.isValid()){
        return;
    }

    IHttpControllerParameter::destroyArguments(methodNode, params);
    request.m_connection->doWrite();
}

$PackageWebCoreEnd
