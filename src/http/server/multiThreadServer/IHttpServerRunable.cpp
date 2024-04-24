#include "IHttpServerRunable.h"
#include "core/base/ISocketUtil.h"
#include "core/config/IProfileImport.h"
#include "http/controller/IHttpManage.h"
#include "http/controller/private/IHttpControllerParameter.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/net/impl/IReqRespRaw.h"
#include "http/response/IFileResponse.h"
#include "http/response/IRendererResponse.h"
#include "http/response/IHtmlResponse.h"
#include "http/response/IResponseTemplateRenderer.h"

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

    do {
        if(!request.valid()){
            break;
        }

        if( IHttpManage::preIntercept(request, response)){
            break;
        }
        if(!request.valid()){
            break;
        }

        IHttpManage::preProcess(request, response);
        if(!request.valid()){
            break;
        }

        handleRequest(request, response);
        if(!request.valid()){
            break;
        }

        if(IHttpManage::postIntercept(request, response)){
            break;
        }
        IHttpManage::postProcess(request, response);
        
        if(!request.valid()){
            break;
        }
    } while(0);

    if(!request.valid()){
        qDebug() << "invalid response";
    }

    if(!response.respond()){
        return ISocketUtil::handleInternalError(request.getRaw()->m_socket);
    }
}

void IHttpServerRunable::handleRequest(IRequest &request, IResponse &response)
{
    if(request.method() == IHttpMethod::OPTIONS){
        return runOptionsFunction(request, response);
    }

    static auto controllerManage = IHttpManage::instance();
    static bool isUrlActionEnabled = controllerManage->isUrlActionNodeEnabled();     // process as dynamic server first
    if(isUrlActionEnabled){
        auto function = controllerManage->getUrlActionNode(request);
        if(function != nullptr){
            if(function->type == IUrlActionNode::Method){
                return processInMethodMode(request, response, function);
            }
            return processInFunctionMode(request, response, function);
        }
    }

    static bool isStaticFileEnabled = controllerManage->isStaticFileActionPathEnabled();        // process as static file server then
    static $Bool handleDir{"http.fileService.folderHandled"};
    if(isStaticFileEnabled && request.method() == IHttpMethod::GET){
        auto path = controllerManage->getStaticFileActionPath(request);
        if(!path.isEmpty()){
            return processInStaticFileMode(request, response, path);
        }
        if(handleDir){
            auto entries = controllerManage->getStaticFolderActionPath(request);
            if(!entries.isEmpty()){
                return processInStaticFolderMode(request, response, entries);
            }
        }
    }

    processInNotFoundMode(request, response);
}

//void IHttpServerRunable::runStatusFunction(IRequest &request, IResponse &response, IStatusActionNode *function)
//{
//    Q_UNUSED(response)
//    IHttpControllerParameter::ParamType params;
//    bool ok = IHttpControllerParameter::createArguments(function->methodNode, params, request);
//    if(!ok){
//        IHttpControllerParameter::destroyArguments(function->methodNode, params);
//        return;
//    }

//    auto index = function->methodNode.metaMethod.methodIndex();
//    auto enclosingObject = function->methodNode.metaMethod.enclosingMetaObject();
//    enclosingObject->static_metacall(QMetaObject::InvokeMetaMethod, index, params);

//    IHttpControllerParameter::destroyArguments(function->methodNode, params);
//}

void IHttpServerRunable::processInFunctionMode(IRequest &request, IResponse &response, IUrlActionNode *node)
{
    node->functionNode.function(request, response);
}

void IHttpServerRunable::processInMethodMode(IRequest &request, IResponse &response, IUrlActionNode *node)
{
    IHttpControllerParameter::ParamType params;
    auto ok = IHttpControllerParameter::createArguments(node->methodNode, params, request);
    if(!ok){
        IHttpControllerParameter::destroyArguments(node->methodNode, params);
        return;
    }

    auto index = node->methodNode.metaMethod.methodIndex();
    auto enclosingObject = node->methodNode.metaMethod.enclosingMetaObject();
    enclosingObject->static_metacall(QMetaObject::InvokeMetaMethod, index, params);
    IHttpControllerParameter::resolveReturnValue(response, node->methodNode, params);
    IHttpControllerParameter::destroyArguments(node->methodNode, params);
}

void IHttpServerRunable::processInStaticFileMode(IRequest &request, IResponse &response, const QString &path)
{
    Q_UNUSED(request)
    IFileResponse fileResponse(path);
    response.setContent(&fileResponse);
}

void IHttpServerRunable::processInStaticFolderMode(IRequest &request, IResponse &response, const QStringList& entries)
{
    auto renderTemplate = IResponseManage::instance()->getTemplateRenderer();
    if(!renderTemplate){
        return;
    }

    auto path = renderTemplate->getPage(IResponseTemplateRenderer::PageType::Directory);
    QJsonObject obj;
    obj["url"] = request.url();
    obj["children"] = QJsonArray::fromStringList(entries);
    obj["isRoot"] = request.url() == "/";
    IRendererResponse nodyResponse(path, obj);
    response.setContent(&nodyResponse);
}

void IHttpServerRunable::processInNotFoundMode(IRequest &request, IResponse &response)
{
    Q_UNUSED(response)
    QString info = request.url() + " " + IHttpMethodUtil::toString(request.method()) + " has no function to handle";
    request.setInvalid(IHttpStatus::NOT_FOUND_404, info);
    return;
}

QStringList handleOptionsRequest(IRequest& request, IResponse& response)
{
    Q_UNUSED(response)
    static auto controllerManage = IHttpManage::instance();
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

//bool IHttpServerRunable::interceptStatusCode(IRequest &request, IResponse &response)
//{
//    auto function = IHttpManage::getStatusActionNode(response.status());
//    if(function != nullptr){
//        runStatusFunction(request, response, function);
//    }
//    return false;
//}

$PackageWebCoreEnd
