#include "IHttpRequestHandler.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/controller/IHttpManage.h"
#include "http/controller/private/IHttpControllerParameter.h"
#include "http/net/server/IHttpConnection.h"
#include "http/invalid/IHttpInvalidManage.h"
#include "http/invalid/IHttpNotFoundInvalid.h"
#include "http/node/IFunctionNode.h"
#include "http/node/IMethodNode.h"
#include "http/node/IUrlActionNode.h"
#include "http/response/IFileResponse.h"
#include "http/response/IRendererResponse.h"
#include "http/response/IResponseTemplateRenderer.h"

$PackageWebCoreBegin

IHttpRequestHandler::IHttpRequestHandler()
{

}

void IHttpRequestHandler::handle(IRequest &request)
{
    IResponse response(&request);
    do{
        if(!request.valid()){
            break;
        }

        handleRequest(request, response);
        if(!request.valid()){
            break;
        }
    }while(0);

    if(!request.valid()){
        auto process = IHttpInvalidManage::instance()->getWare(request.getRaw()->m_responseRaw->content.contentInvalid.tag);
        process->process(request, response);
    }
    request.m_connection->doWrite();
}

void IHttpRequestHandler::handleRequest(IRequest &request, IResponse &response)
{
    if(request.method() == IHttpMethod::OPTIONS){
        runOptionsFunction(request, response);
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

    QString info = request.url() + " " + IHttpMethodUtil::toString(request.method()) + " has no function to handle";
    response.setContent(IHttpNotFoundInvalid(info));

}

void IHttpRequestHandler::runOptionsFunction(IRequest &request, IResponse &response)
{
    QStringList  options = handleOptionsRequest(request, response);

    response.setStatus(IHttpStatusCode::OK_200);
    if(options.isEmpty()) {
        response.setHeader("Allow" , "NONE");
    } else {
        response.setHeader("Allow" , options.join(", "));
    }
    response.setContent("");
}

QStringList IHttpRequestHandler::handleOptionsRequest(IRequest &request, IResponse &response)
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

void IHttpRequestHandler::processInMethodMode(IRequest &request, IResponse &response, IUrlActionNode *node)
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
    if(!request.valid()){
        return;
    }

    IHttpControllerParameter::resolveReturnValue(response, node->methodNode, params);
    if(!request.valid()){
        return;
    }

    IHttpControllerParameter::destroyArguments(node->methodNode, params);
}

void IHttpRequestHandler::processInFunctionMode(IRequest &request, IResponse &response, IUrlActionNode *node)
{
    node->functionNode.function(request, response);
}

void IHttpRequestHandler::processInStaticFileMode(IRequest &request, IResponse &response, const QString &path)
{
    Q_UNUSED(request)
    IFileResponse fileResponse(path);
    response.setContent(&fileResponse);
}

void IHttpRequestHandler::processInStaticFolderMode(IRequest &request, IResponse &response, const QStringList &entries)
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

$PackageWebCoreEnd
