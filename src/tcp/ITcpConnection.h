#pragma once

#include "core/util/IHeaderUtil.h"
#include <queue>

$PackageWebCoreBegin

class ITcpResolver;

class ITcpConnection
{
    friend class ITcpResolver;
public:
    ITcpConnection(asio::ip::tcp::socket&& socket, int resolverFactoryId);
    virtual ~ITcpConnection();

public:
    void doRead();
    void doReadStreamBy(int length, bool isData = true);
    void doReadStreamUntil(IStringView);
    void doWrite();

    void doReadResolverFinished();
    void doWriteResolverFinished();
    void doReadError(std::error_code);
    void doWriteError(std::error_code);

public:
    void addResolver(ITcpResolver*);

private:
    asio::ip::tcp::socket m_socket;
    std::queue<ITcpResolver*> m_resolvers;
    bool m_closeConnection{true};
    int m_resolverFactoryId{};
};

$PackageWebCoreEnd
