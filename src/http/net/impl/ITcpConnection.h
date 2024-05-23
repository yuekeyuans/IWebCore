#pragma once

#include "core/base/IHeaderUtil.h"
#include "http/net/server/ITcpConnectionData.h"


$PackageWebCoreBegin

class ITcpResolverInterface;

class ITcpConnection
{
public:
    ITcpConnection(asio::ip::tcp::socket socket);
    virtual ~ITcpConnection() = default;

public:
    void doRead();
    void doWrite();
    void doDestroy();
    void doReuse();

private:
    asio::ip::tcp::socket m_socket;
    ITcpConnectionData m_data;
    ITcpResolverInterface* m_resolver{};
};

$PackageWebCoreEnd
