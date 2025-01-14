#pragma once

#include "core/util/IHeaderUtil.h"
#include "tcp/ITcpResolver.h"

$PackageWebCoreBegin

class ITcpConnection;
class ITcpResolverFactoryWare
{
public:
    ITcpResolverFactoryWare() = default;
    virtual ~ITcpResolverFactoryWare() = default;

public:
    virtual IString getName() = 0;
    virtual ITcpResolver* createResolver(ITcpConnection&, int) = 0;
    virtual void destroyResolver(ITcpResolver*) = 0;
};

$PackageWebCoreEnd
