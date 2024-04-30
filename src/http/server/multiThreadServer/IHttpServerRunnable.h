#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;
struct IUrlActionNode;

class IHttpServerRunnable : public QRunnable
{
public:
    IHttpServerRunnable(qintptr handle);
    IHttpServerRunnable(QTcpSocket* socket);
    virtual void run() final;

private:
    static void runRequest(IRequest& req);

    static void handleRequest(IRequest& request, IResponse& response);
    static void processInFunctionMode(IRequest& request, IResponse& response, IUrlActionNode* node);
    static void processInMethodMode(IRequest& request, IResponse& response, IUrlActionNode* node);
    static void processInStaticFileMode(IRequest& request, IResponse& response, const QString& path);
    static void processInStaticFolderMode(IRequest& request, IResponse& response, const QStringList& entries);
    static void processInNotFoundMode(IRequest& request, IResponse& response);
    static void runOptionsFunction(IRequest& request, IResponse& response);
private:
    qintptr m_handle{0};
    QTcpSocket* m_socket{nullptr};
};

$PackageWebCoreEnd
