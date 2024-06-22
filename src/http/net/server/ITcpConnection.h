#pragma once

#include "core/base/IHeaderUtil.h"
#include "http/net/server/ITcpConnectionData.h"

$PackageWebCoreBegin

class ITcpResolverInterface;

class ITcpConnection
{
    friend class ITcpResolverInterface;
public:
    ITcpConnection(asio::ip::tcp::socket socket);
    virtual ~ITcpConnection();

public:
    void doRead();
    void doReadStreamBy(int length);
    void doReadStreamUntil(IStringView);
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
};

$PackageWebCoreEnd
