#include "IInterceptInterface.h"

$PackageWebCoreBegin

IInterceptInterface::IInterceptInterface()
{
}

IInterceptInterface::~IInterceptInterface()
{

}

bool IInterceptInterface::intercept(QTcpSocket &socket)
{
    Q_UNUSED(socket)
    qFatal("this function should not use directly");
    return false;
}

bool IInterceptInterface::intercept(IRequest &request)
{
    Q_UNUSED(request)
    qFatal("this function should not use directly");
    return false;
}

bool IInterceptInterface::intercept(IRequest &request, IResponse &response)
{
    Q_UNUSED(request)
    Q_UNUSED(response)
    qFatal("this function should not use directly");
    return false;
}


$PackageWebCoreEnd
