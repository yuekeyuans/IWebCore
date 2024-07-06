#include "IHttpRequestHandler.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/controller/IHttpManage.h"
#include "http/controller/private/IHttpControllerParameter.h"
#include "http/server/IHttpConnection.h"
#include "http/invalid/IHttpInvalidManage.h"
#include "http/invalid/IHttpNotFoundInvalid.h"
#include "http/base/IFunctionNode.h"
#include "http/base/IMethodNode.h"
#include "http/controller/private/IHttpControllerActionNode.h"
#include "http/response/IFileResponse.h"
#include "http/response/IRendererResponse.h"
#include "http/response/IResponseTemplateRenderer.h"

$PackageWebCoreBegin

void IHttpRequestHandler::handle(IRequest &request)
{
    IResponse response(&request);
    do{
        if(!request.isValid()){
            break;
        }

        handleRequest(request, response);
        if(!request.isValid()){
            break;
        }
    }while(0);

    if(!request.isValid()){
        auto process = IHttpInvalidManage::instance()->getWare(request.getRaw()->m_responseRaw->content.contentInvalid.tag);
        process->process(request, response);
    }
    request.m_connection->doWrite();
}

void IHttpRequestHandler::handleRequest(IRequest &request, IResponse &response)
{
    const auto& process = request.getRaw()->m_processer;

    if(process.type == IRequestRaw::ProcessUnit::Option){
        runOptionsFunction(request, response);
    }

    switch (process.type) {
    case IRequestRaw::ProcessUnit::Option:
        return runOptionsFunction(request, response);
    case IRequestRaw::ProcessUnit::Function:
    {
        auto function = process.node;
        if(function->type == IHttpControllerActionNode::Method){
            return processInMethodMode(request, response, function);
        }
        return processInFunctionMode(request, response, function);
    }
    case IRequestRaw::ProcessUnit::Path:
        return processInStaticFileMode(request, response, process.path);
    case IRequestRaw::ProcessUnit::Directory:
        return processInStaticFolderMode(request, response, process.entries);
    default:
    {
        QString info = request.url().toQString() + " " + IHttpMethodUtil::toString(request.method()) + " has no function to handle";
        response.setContent(IHttpNotFoundInvalid(info));
    }
    }
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

void IHttpRequestHandler::processInMethodMode(IRequest &request, IResponse &response, IHttpControllerActionNode *node)
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
    if(!request.isValid()){
        return;
    }

    IHttpControllerParameter::resolveReturnValue(response, node->methodNode, params);
    if(!request.isValid()){
        return;
    }

    IHttpControllerParameter::destroyArguments(node->methodNode, params);
}

void IHttpRequestHandler::processInFunctionMode(IRequest &request, IResponse &response, IHttpControllerActionNode *node)
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
    obj["url"] = QString(request.url());
    obj["children"] = QJsonArray::fromStringList(entries);
    obj["isRoot"] = request.url() == "/";
    IRendererResponse nodyResponse(path, obj);
    response.setContent(&nodyResponse);
}

$PackageWebCoreEnd
