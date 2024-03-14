#include "IHttpServerRunable.h"
#include "core/base/ISocketUtil.h"
#include "web/controller/IControllerManage.h"
#include "web/controller/private/IControllerParamUtil.h"
#include "web/net/IRequest.h"
#include "web/net/IResponse.h"
#include "web/net/impl/IReqRespRaw.h"
#include "web/response/IFileResponse.h"

$PackageWebCoreBegin

IHttpServerRunable::IHttpServerRunable(qintptr handle) : m_handle{handle}
{

}

IHttpServerRunable::IHttpServerRunable(QTcpSocket *socket) : m_socket(socket)
{

}

void IHttpServerRunable::run()
{
    if(m_socket != nullptr){
        IRequest request(m_socket);
        runRequest(request);
    }else{
        IRequest request(m_handle);
        runRequest(request);
    }
}

void IHttpServerRunable::runRequest(IRequest& request)
{
    IResponse response(&request);
    if(!request.valid()){
        response.respond();
        return;
    }

    do {
        if( IControllerManage::preIntercept(request, response)){
            break;
        }
        IControllerManage::preProcess(request, response);
        if(!request.valid()){
            break;
        }

        handleRequest(request, response);
        if(!request.valid()){
            break;
        }

        if(IControllerManage::postIntercept(request, response)){
            break;
        }
        IControllerManage::postProcess(request, response);
        
        // 拦截 socket
        if(!response.valid() || response.status() != IHttpStatus::OK_200){
            if(interceptStatusCode(request, response)){
                break;
            }
        }

    } while(0);

    if(!response.respond()){
        return ISocketUtil::handleInternalError(request.getRaw()->m_socket);
    }
}

void IHttpServerRunable::handleRequest(IRequest &request, IResponse &response)
{
    static auto controllerManage = IControllerManage::instance();
    if(request.method() == IHttpMethod::OPTIONS){
        return runOptionsFunction(request, response);
    }

    static bool isUrlActionEnabled = controllerManage->isUrlActionNodeEnabled();     // process as dynamic server first
    if(isUrlActionEnabled){
        auto function = controllerManage->getUrlActionNode(request);
        if(function != nullptr){
            if(function->type == IUrlActionNode::Method){
                processInMethodMode(request, response, function);
            }else if(function->type == IUrlActionNode::Function){
                processInFunctionMode(request, response, function);
            }
            return;
        }
    }

    static bool isStaticFileEnabled = controllerManage->isStaticFileActionPathEnabled();        // process as static file server then
    if(isStaticFileEnabled && request.method() == IHttpMethod::GET){
        auto path = controllerManage->getStaticFileActionPath(request);
        if(!path.isEmpty()){
            processInStaticFileMode(request, response, path);
            return;
        }
    }

    // process as not found last
    processInNotFoundMode(request, response);
}

void IHttpServerRunable::runStatusFunction(IRequest &request, IResponse &response, IStatusActionNode *function)
{
    Q_UNUSED(response)
    IControllerParamUtil::ParamType params;
    bool ok = IControllerParamUtil::createArguments(function->methodNode, params, request);
    if(!ok){
        IControllerParamUtil::destroyArguments(function->methodNode, params);
        return;
    }

    auto index = function->methodNode.metaMethod.methodIndex();
    auto enclosingObject = function->methodNode.metaMethod.enclosingMetaObject();
    enclosingObject->static_metacall(QMetaObject::InvokeMetaMethod, index, params);

    IControllerParamUtil::destroyArguments(function->methodNode, params);
}

void IHttpServerRunable::processInFunctionMode(IRequest &request, IResponse &response, IUrlActionNode *node)
{
    node->functionNode.function(request, response);
}

void IHttpServerRunable::processInMethodMode(IRequest &request, IResponse &response, IUrlActionNode *node)
{
    IControllerParamUtil::ParamType params;
    auto ok = IControllerParamUtil::createArguments(node->methodNode, params, request);
    if(!ok){
        IControllerParamUtil::destroyArguments(node->methodNode, params);
        return;
    }

    auto index = node->methodNode.metaMethod.methodIndex();
    auto enclosingObject = node->methodNode.metaMethod.enclosingMetaObject();
    enclosingObject->static_metacall(QMetaObject::InvokeMetaMethod, index, params);
    IControllerParamUtil::resolveReturnValue(response, node->methodNode, params);

    IControllerParamUtil::destroyArguments(node->methodNode, params);
}

void IHttpServerRunable::processInStaticFileMode(IRequest &request, IResponse &response, const QString &path)
{
    Q_UNUSED(request)
    IFileResponse staticFileReponse(path);
    response.setContent(&staticFileReponse);
}

void IHttpServerRunable::processInNotFoundMode(IRequest &request, IResponse &response)
{
    Q_UNUSED(response)
    QString info = request.url() + " " + IHttpMethodHelper::toString(request.method()) + " has no function to handle";
    request.setInvalid(IHttpStatus::NOT_FOUND_404, info);
    return;
}

QStringList handleOptionsRequest(IRequest& request, IResponse& response)
{
    Q_UNUSED(response)
    static auto controllerManage = IControllerManage::instance();
    static const QMap<IHttpMethod, QString> mappings = {
        {IHttpMethod::GET,      "GET"},
        {IHttpMethod::PUT,      "PUT"},
        {IHttpMethod::POST,     "POST"},
        {IHttpMethod::DELETED,  "DELETE"},
        {IHttpMethod::PATCH,    "PATCH"},
    };
    static const QList<IHttpMethod> keys = mappings.keys();

    QStringList options;
    auto raw = request.getRaw();
    auto origin = raw->m_method;
    for (auto key : keys) {
        raw->m_method = key;
        if(controllerManage->getUrlActionNode(request) != nullptr){
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

void IHttpServerRunable::runOptionsFunction(IRequest &request, IResponse &response)
{
    QStringList  options = handleOptionsRequest(request, response);

    response.setStatus(IHttpStatus::OK_200);
    if(options.isEmpty()) {
        response.setHeader("Allow" , "NONE");
    } else {
        response.setHeader("Allow" , options.join(", "));
    }
    response.setContent("");
}

bool IHttpServerRunable::interceptStatusCode(IRequest &request, IResponse &response)
{
    auto function = IControllerManage::getStatusActionNode(response.status());
    if(function != nullptr){
        runStatusFunction(request, response, function);
    }
    return false;
}

$PackageWebCoreEnd
