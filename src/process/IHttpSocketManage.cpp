#include "IHttpSocketManage.h"
#include "IHttpRunner.h"
#include "base/IMetaUtil.h"
#include "base/ISocketUtil.h"
#include "base/ITicTacUtil.h"
#include "common/net/IResponse.h"
#include "common/net/IRequest.h"
#include "common/net/impl/IReqRespRaw.h"
#include "IHttpProcesser.h"
#include "controller/IControllerManage.h"
#include "support/IRequestErrorPreIntercept.h"

$PackageWebCoreBegin

IHttpSocketManage::IHttpSocketManage()
{
}

void IHttpSocketManage::addSocket(qintptr handle)
{
    auto runable = new IHttpProcesser(handle);
    instance()->pool.start(runable);
}

bool IHttpSocketManage::interceptStatusCode(IRequest &request, IResponse &response)
{
    auto function = IControllerManage::getStatusFunction(response.status());
    if(function != nullptr){
        IHttpRunner::runStatusFunction(request, response, function);
    }
    return false;
}

void IHttpSocketManage::handleRequest(IRequest &request, IResponse &response)
{
    if(request.method() == IHttpMethod::OPTIONS){
        return handleOptionsRequest(request, response);
    }

    auto function = IControllerManage::getUrlFunction(request);
    if(function == nullptr){
        request.setInvalid(IHttpStatus::NOT_FOND_404, request.url() + " " + IHttpMethodHelper::toString(request.method()) +  " has no function to handle");
        return;
    }

    IHttpRunner::runUrlFunction(request, response, function);
}

void IHttpSocketManage::handleOptionsRequest(IRequest &request, IResponse &response)
{
    QStringList options;
    options.append("OPTIONS");

    // the origin is equal to OPTIONS
    auto raw = request.getRaw();
    auto origin = raw->m_method;

    raw->m_method = IHttpMethod::GET;
    if(IControllerManage::getUrlFunction(request) != nullptr){
        options.append("GET");
        options.append("HEAD");
    }

    raw->m_method = IHttpMethod::PUT;
    if(IControllerManage::getUrlFunction(request) != nullptr){
        options.append("PUT");
    }

    raw->m_method = IHttpMethod::POST;
    if(IControllerManage::getUrlFunction(request) != nullptr){
        options.append("POST");
    }

    raw->m_method = IHttpMethod::DELETED;
    if(IControllerManage::getUrlFunction(request) != nullptr){
        options.append("DELETE");
    }

    raw->m_method = IHttpMethod::PATCH;
    if(IControllerManage::getUrlFunction(request) != nullptr){
        options.append("PATCH");
    }

    raw->m_method = origin;

    return IHttpRunner::runOptionsFunction(request, response, options);
}

void IHttpSocketManage::processResponseError(IResponse &response, QTcpSocket **socket)
{
    Q_UNUSED(response)
    ISocketUtil::closeTcpSocket(socket);
}

void IHttpSocketManage::processResponseNotFound(IResponse &response, QTcpSocket **socket)
{
    Q_UNUSED(response);
    Q_UNUSED(socket);
}

$PackageWebCoreEnd

