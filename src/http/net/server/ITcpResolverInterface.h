#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class ITcpConnection;
class ITcpResolverInterface
{
protected:

public:
    ITcpResolverInterface(ITcpConnection* connection);
   virtual ~ITcpResolverInterface() = default;

public:
    virtual void resolve() = 0;
    virtual QByteArray getResult() = 0;

public:
    ITcpConnection* m_connection{};
};

$PackageWebCoreEnd
