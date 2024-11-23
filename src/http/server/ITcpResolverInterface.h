#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

// NOTE: 这个设计的目的是能够扩展使用范围，不仅仅是 http 协议能够使用，其他协议也能够使用。

class ITcpConnection;
class ITcpResolverInterface
{
protected:

public:
    ITcpResolverInterface(ITcpConnection* connection);
   virtual ~ITcpResolverInterface() = default;

public:
    virtual void resolve() = 0;
    virtual std::vector<asio::const_buffer> getOutput() = 0;

public:
    ITcpConnection* m_connection{};
};

$PackageWebCoreEnd
