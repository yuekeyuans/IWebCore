#pragma once

#include "base/IHeaderUtil.h"
#include "biscuits/IHttpStatus.h"
#include "base/IPreProcessorUtil.h"

$PackageWebCoreBegin

class IResponse;
class IRequest;
class IResponsePostProcessInterface;
class IResponsePostInterceptInterface;
class IRequestPreInterceptorInterface;
class IRequestPreProcessInterface;
class IStatusPageInterface;

class IHttpSocketManage
{
    $UseInstance(IHttpSocketManage)
private:
    IHttpSocketManage();

public:
    static void addSocket(qintptr handle);

    static bool interceptStatusCode(IRequest& request, IResponse& response);

    static void handleRequest(IRequest& request, IResponse& response);
    static void handleOptionsRequest(IRequest& request, IResponse& response);

    /// 当 response 解析产生错误时调用
    static void processResponseError(IResponse& response, QTcpSocket** socket);

    // 当 没有发现处理函数时调用
    static void processResponseNotFound(IResponse& response, QTcpSocket** socket);

private:
    QThreadPool pool;
    QVector<IRequestPreInterceptorInterface *> preIntercepters;
    QVector<IRequestPreProcessInterface *> preProcessors;
    QVector<IResponsePostInterceptInterface *> postIntercepters;
    QVector<IResponsePostProcessInterface*> postProcessors;
};

$PackageWebCoreEnd
