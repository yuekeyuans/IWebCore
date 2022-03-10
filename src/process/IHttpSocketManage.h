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

    static void processResponseError(IResponse& response, QTcpSocket** socket);     /// 当 response 解析产生错误时调用

    static void processResponseNotFound(IResponse& response, QTcpSocket** socket);      // 当 没有发现处理函数时调用

private:
    QThreadPool pool;
};

$PackageWebCoreEnd
