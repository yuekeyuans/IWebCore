#pragma once

#include "tcp/ITcpResolverFactoryInterface.h"
#include "http/IRequest.h"
#include "core/util/IMemoryObjectPool.h"

$PackageWebCoreBegin

class IHttpResolverFactory : public ITcpResolverFactoryInterface<IHttpResolverFactory, IRequest>
{
public:
    IHttpResolverFactory() = default;

public:
    virtual IString getName() final;
};

$PackageWebCoreEnd
