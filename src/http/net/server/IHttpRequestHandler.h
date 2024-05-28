#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;
class IHttpRequestHandler
{
public:
    IHttpRequestHandler();

public:
    void handle(IRequest& request);

private:
    void handleRequest(IRequest& request, IResponse& response);
};

$PackageWebCoreEnd
