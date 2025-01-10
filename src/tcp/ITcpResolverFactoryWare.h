#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class ITcpResolver;
class ITcpConnection;
class ITcpResolverFactoryWare
{
public:
    ITcpResolverFactoryWare();

public:
    virtual IString getName() = 0;
    virtual ITcpResolver* createResolver(ITcpConnection&) = 0;
};

$PackageWebCoreEnd
