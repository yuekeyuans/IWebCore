#include "IHttpResolverFactory.h"
#include "http/IRequest.h"
#include "tcp/ITcpConnection.h"

$PackageWebCoreBegin

IString IHttpResolverFactory::getName()
{
    static std::string name = "http";
    return IString(&name);
}

$PackageWebCoreEnd
