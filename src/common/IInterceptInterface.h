#pragma once

#include "base/IHeaderUtil.h"

class QTcpSocket;
class IRequest;
class IResponse;

$PackageWebCoreBegin

class IInterceptInterface
{
public:
    enum PositionType{
        IP_AND_PORT_INTERCEPT,
        URL_METHOD_VERSION_INTERCEPT,
        REQUEST_HEAD_INTERCEPT,
        REQUEST_RESOLVE_FINISHED_INTERCEPT,

    };

    enum FunType{
        SOCKET,
        REQUEST,
        REUQEST_RESPONSE
    };

    IInterceptInterface();
    virtual ~IInterceptInterface();

    virtual PositionType getPositionType() = 0;
    virtual FunType getFunType() = 0;

    virtual bool intercept(QTcpSocket& socket);
    virtual bool intercept(IRequest& request);
    virtual bool intercept(IRequest& request, IResponse& response);
};


$PackageWebCoreEnd
