#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;
class IUrlActionNode;
class IHttpRequestHandler
{
public:
    IHttpRequestHandler();

public:
    void handle(IRequest& request);

private:
    void handleRequest(IRequest& request, IResponse& response);

private:
    void runOptionsFunction(IRequest &request, IResponse &response);
    QStringList handleOptionsRequest(IRequest& request, IResponse& response);

    void processInMethodMode(IRequest &request, IResponse &response, IUrlActionNode *node);
    void processInFunctionMode(IRequest &request, IResponse &response, IUrlActionNode *node);
    void processInStaticFileMode(IRequest &request, IResponse &response, const QString &path);
    void processInStaticFolderMode(IRequest &request, IResponse &response, const QStringList& entries);


};

$PackageWebCoreEnd
