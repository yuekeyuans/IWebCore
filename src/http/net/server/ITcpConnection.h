#pragma once

#include "core/base/IHeaderUtil.h"
#include "http/net/server/ITcpConnectionData.h"

$PackageWebCoreBegin

class ITcpResolverInterface;

class ITcpConnection
{
public:
    ITcpConnection(asio::ip::tcp::socket socket);
    virtual ~ITcpConnection();

public:
    void doRead();
    void doReadStreamUntil(const char*);
    void doWrite();
    void doDestroy();
    void doReuse();

private:
    void resolveData();

public:
    ITcpConnectionData m_data;

private:
    asio::ip::tcp::socket m_socket;
    ITcpResolverInterface* m_resolver{};
    bool m_closeConnection{true};

public:
    friend class ITcpResolverInterface;
};

$PackageWebCoreEnd
