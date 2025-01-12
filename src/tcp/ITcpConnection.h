#pragma once

#include "core/util/IHeaderUtil.h"
#include <queue>

$PackageWebCoreBegin

class ITcpResolver;

class IResolvers : public std::deque<ITcpResolver*>
{
public:
    void deleteFront();

    void deleteBack();

    void push_back(ITcpResolver*);
private:
    std::mutex m_mutex;
};

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
    asio::ip::tcp::socket m_socket;
    IResolvers m_resolvers;
};

$PackageWebCoreEnd
