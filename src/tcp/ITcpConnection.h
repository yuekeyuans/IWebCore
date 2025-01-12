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

    void doReadFinished();
    void doWriteFinished();
    void doReadError(std::error_code);
    void doWriteError(std::error_code);

public:
    void addResolver(ITcpResolver*);

public:
    bool m_keepAlive{false};
    int m_resolverFactoryId;

private:
    std::mutex m_mutex;
    asio::ip::tcp::socket m_socket;
    std::deque<ITcpResolver*> m_resolvers;
};

$PackageWebCoreEnd
