#include "IHttpResolverFactory.h"
#include "http/net/IRequest.h"
#include "tcp/ITcpConnection.h"

$PackageWebCoreBegin

IString IHttpResolverFactory::getName()
{
    static std::string name = "http";
    return IString(&name);
}

ITcpResolver *IHttpResolverFactory::createResolver(ITcpConnection &connection)
{
    return new IRequest(connection);
}

$PackageWebCoreEnd
