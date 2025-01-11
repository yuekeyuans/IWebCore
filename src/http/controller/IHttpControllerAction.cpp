#include "IHttpControllerAction.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/net/impl/IRequestRaw.h"
#include "tcp/ITcpConnection.h"

$PackageWebCoreBegin

void IHttpControllerAction::invoke(IRequest &request) const
{
    auto params = createParams(request);
    if(request.isValid()){
        auto index = m_methodNode.metaMethod.methodIndex();
        auto enclosingObject = m_methodNode.metaMethod.enclosingMetaObject();
        enclosingObject->static_metacall(QMetaObject::InvokeMetaMethod, index, params.data());
        if(request.isValid()){
            m_methodNode.returnNode.m_resolveFunction(request.impl(), params[0]);
        }
    }

    destroyParams(params);
    request.startWrite();
}

IHttpControllerAction::ParamType IHttpControllerAction::createParams(IRequest& request) const
{
    ParamType params{0};
    params[0] = m_methodNode.returnNode.create();
    int len = m_methodNode.argumentNodes.length();
    for(int i=0; i<len; i++){
        params[i+1] = m_methodNode.argumentNodes[i].m_createFun(request);
        if(!request.isValid()){
            break;
        }
    }
    return params;
}

void IHttpControllerAction::destroyParams(const IHttpControllerAction::ParamType& params) const
{
    m_methodNode.returnNode.destroy(params[0]);
    int len = m_methodNode.argumentNodes.length();
    for(int i=0; i<len; i++){
        if(params[i+1] && m_methodNode.argumentNodes[i].m_destroyFun){
            m_methodNode.argumentNodes[i].m_destroyFun(params[i+1]);
        }
    }
}

$PackageWebCoreEnd
