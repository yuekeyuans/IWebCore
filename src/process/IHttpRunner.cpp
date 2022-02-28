#include "IHttpRunner.h"
#include "common/net/IRequest.h"
#include "common/net/IResponse.h"
#include "common/node/IFunctionNode.h"
#include "common/node/IStatusFunctionNode.h"
#include "common/node/IUrlFunctionNode.h"

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

// TODO: 这里的 runUrlFunction 可以考虑 返回 一个 函数调用， 调用另外一个函数
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

void IHttpRunner::runOptionsFunction(IRequest &request, IResponse &response, const QStringList &options)
{
    Q_UNUSED(request)
    response.setStatus(IHttpStatus::OK_200);
    if(options.isEmpty()){
        response.setHeader("Allow" , "NONE");
    }else{
        response.setHeader("Allow" , options.join(", "));
    }
    response.setContent("");
}

$PackageWebCoreEnd
