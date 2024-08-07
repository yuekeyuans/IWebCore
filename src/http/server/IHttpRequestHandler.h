﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;
struct IHttpControllerActionNode;
class IHttpRequestHandler : public ISingletonUnit<IHttpRequestHandler>
{
public:
    IHttpRequestHandler() = default;

public:
    void handle(IRequest& request);

private:
    void handleRequest(IRequest& request, IResponse& response);

private:
    void runOptionsFunction(IRequest &request, IResponse &response);
    QStringList handleOptionsRequest(IRequest& request, IResponse& response);

    void processInMethodMode(IRequest &request, IResponse &response, IHttpControllerActionNode *node);
    void processInFunctionMode(IRequest &request, IResponse &response, IHttpControllerActionNode *node);
    void processInStaticFileMode(IRequest &request, IResponse &response, const QString &path);
    void processInStaticFolderMode(IRequest &request, IResponse &response, const QStringList& entries);
};

$PackageWebCoreEnd
