#include "ITcpResolverManage.h"
#include "http/net/IRequest.h"

$PackageWebCoreBegin

ITcpResolverInterface *ITcpResolverManage::createResolver(ITcpConnection *connection)
{
    return new IRequest(connection);
}

$PackageWebCoreEnd
