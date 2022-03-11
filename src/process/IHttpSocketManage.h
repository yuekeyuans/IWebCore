#pragma once

#include "base/IHeaderUtil.h"
#include "biscuits/IHttpStatus.h"
#include "base/IPreProcessorUtil.h"

$PackageWebCoreBegin

class IResponse;
class IRequest;
class IStatusPageInterface;

class IHttpSocketManage
{
    $UseInstance(IHttpSocketManage)
private:
    IHttpSocketManage() = default;

public:
    static void addSocket(qintptr handle);

    static bool interceptStatusCode(IRequest& request, IResponse& response);

private:
    QThreadPool pool;
};

$PackageWebCoreEnd
