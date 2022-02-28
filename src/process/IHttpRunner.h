#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;
struct IStatusFunctionNode;
struct IUrlFunctionNode;

class IHttpRunner
{
    $UseInstance(IHttpRunner)
private:
    IHttpRunner() = default;

public:
    static void runStatusFunction(IRequest& request, IResponse& response, IStatusFunctionNode* function);
    static void runUrlFunction(IRequest& request, IResponse& response, IUrlFunctionNode* function);
    static void runOptionsFunction(IRequest& request, IResponse& response, const QStringList& options);
};

$PackageWebCoreEnd
