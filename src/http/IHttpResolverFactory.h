#pragma once

#include "tcp/ITcpResolverFactoryInterface.h"

$PackageWebCoreBegin

class IHttpResolverFactory : public ITcpResolverFactoryInterface<IHttpResolverFactory>
{
public:
    IHttpResolverFactory() = default;

public:
    virtual IString getName() final;
    virtual ITcpResolver* createResolver(ITcpConnection&) final;
};

$PackageWebCoreEnd
