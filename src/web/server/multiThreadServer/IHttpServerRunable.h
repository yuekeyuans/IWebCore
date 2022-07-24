#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;
struct IStatusActionNode;
struct IUrlActionNode;

// TODO: 这里需要一个 IRequestErrorPreIntercept 拦截 valid() == false 的情形。

class IHttpServerRunable : public QRunnable
{
public:
    IHttpServerRunable(qintptr handle);
    IHttpServerRunable(QTcpSocket* socket);
    virtual void run() final;

private:
    static void runContent(IRequest& req);   // TODO:  需要重命名

    static void handleRequest(IRequest& request, IResponse& response);
    static void runStatusFunction(IRequest& request, IResponse& response, IStatusActionNode* function);


    static void processInFunctionMode(IRequest& request, IResponse& response, IUrlActionNode* node);
    static void processInMethodMode(IRequest& request, IResponse& response, IUrlActionNode* node);
    static void processInStaticFileMode(IRequest& request, IResponse& response, const QString& path);
    static void processInNotFoundMode(IRequest& request, IResponse& response);

    static void runOptionsFunction(IRequest& request, IResponse& response);

    static bool interceptStatusCode(IRequest& request, IResponse& response);

private:
    qintptr m_handle{0};
    QTcpSocket* m_socket{nullptr};
};

$PackageWebCoreEnd
