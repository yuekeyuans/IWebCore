#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;
struct IStatusFunctionNode;
struct IUrlActionNode;

// TODO: 这里需要一个 IRequestErrorPreIntercept 拦截 valid() == false 的情形。

class IHttpServerRunable : public QRunnable
{
public:
    IHttpServerRunable(qintptr handle);
    virtual void run() final;

private:
    static void handleRequest(IRequest& request, IResponse& response);
    static void runStatusFunction(IRequest& request, IResponse& response, IStatusFunctionNode* function);

    static void processInDynamicUrlFunctionMode(IRequest& request, IResponse& response, IUrlActionNode* function);
    static void processInStaticFileMode(IRequest& request, IResponse& response, const QString& path);
    static void processInNotFoundMode(IRequest& request, IResponse& response);

    static void runOptionsFunction(IRequest& request, IResponse& response);

    static bool interceptStatusCode(IRequest& request, IResponse& response);

private:
    qintptr handle{0};
    QTcpSocket* socket{nullptr};
};

$PackageWebCoreEnd
