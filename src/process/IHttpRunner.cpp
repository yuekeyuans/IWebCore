#include "IHttpRunner.h"
#include "common/net/IRequest.h"
#include "common/net/IResponse.h"
#include "common/net/impl/IReqRespRaw.h"
#include "common/node/IFunctionNode.h"
#include "common/node/IStatusFunctionNode.h"
#include "common/node/IUrlFunctionNode.h"
#include "controller/IControllerManage.h"

#include "process/private/IHttpRunnerHelper.h"

$PackageWebCoreBegin

void IHttpRunner::runStatusFunction(IRequest &request, IResponse &response, IStatusFunctionNode *function)
{
    Q_UNUSED(response)
    IHttpRunnerHelper::ParamType params;
    IHttpRunnerHelper::createParams(function->functionNode, params, request);

    if(!request.valid()){   // unneeded, but write here for assurance
        IHttpRunnerHelper::destroyParams(function->functionNode, params);
        return;
    }

    auto index = function->functionNode.metaMethod.methodIndex();
    auto enclosingObject = function->functionNode.metaMethod.enclosingMetaObject();
    enclosingObject->static_metacall(QMetaObject::InvokeMetaMethod, index, params);

    IHttpRunnerHelper::destroyParams(function->functionNode, params);
}

void IHttpRunner::runUrlFunction(IRequest &request, IResponse &response, IUrlFunctionNode *function)
{
    IHttpRunnerHelper::ParamType params;
    IHttpRunnerHelper::createParams(function->functionNode, params, request);

    if(!request.valid()){           // 这里 request invalid 的情况产生于 数据转换的时候。
        IHttpRunnerHelper::destroyParams(function->functionNode, params);
        return;
    }

    auto index = function->functionNode.metaMethod.methodIndex();
    auto enclosingObject = function->functionNode.metaMethod.enclosingMetaObject();
    enclosingObject->static_metacall(QMetaObject::InvokeMetaMethod, index, params);
    IHttpRunnerHelper::resolveReturnValue(response, function->functionNode, params);

    IHttpRunnerHelper::destroyParams(function->functionNode, params);
}

QStringList handleOptionsRequest(IRequest& request, IResponse& response)
{
    Q_UNUSED(response)
    static const QMap<IHttpMethod, QString> mappings = {
        {IHttpMethod::GET, "GET"},
        {IHttpMethod::PUT, "PUT"},
        {IHttpMethod::POST, "POST"},
        {IHttpMethod::DELETED, "DELETE"},
        {IHttpMethod::PATCH, "PATCH"},
        };
    static const QList<IHttpMethod> keys = mappings.keys();

    QStringList options;
    auto raw = request.getRaw();
    auto origin = raw->m_method;
    for(auto key : keys){
        raw->m_method = key;
        if(IControllerManage::getUrlFunction(request) != nullptr){
            options.append(mappings[key]);
        }
    }

    if(options.contains("GET")){
        options.append("HEAD");
    }
    if(!options.empty()){
        options.append("OPTIONS");
    }

    raw->m_method = origin;

    return options;
}

void IHttpRunner::runOptionsFunction(IRequest &request, IResponse &response)
{
    QStringList  options = handleOptionsRequest(request, response);

    response.setStatus(IHttpStatus::OK_200);
    if(options.isEmpty()){
        response.setHeader("Allow" , "NONE");
    }else{
        response.setHeader("Allow" , options.join(", "));
    }
    response.setContent("");
}

$PackageWebCoreEnd
