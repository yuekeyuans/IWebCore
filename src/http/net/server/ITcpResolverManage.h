#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "http/net/server/ITcpResolverInterface.h"

$PackageWebCoreBegin

class ITcpConnection;

class ITcpResolverManage : public ISingletonUnit<ITcpResolverManage>
{
public:
    ITcpResolverManage() = default;

public:
    ITcpResolverInterface* createResolver(ITcpConnection* connection);
};

$PackageWebCoreEnd
