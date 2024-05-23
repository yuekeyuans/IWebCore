#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class ITcpConnection;
class ITcpResolverInterface
{
public:
    ITcpResolverInterface(ITcpConnection*);
    virtual void resolve() = 0;

public:
    ITcpConnection* m_connection{};
};

$PackageWebCoreEnd
