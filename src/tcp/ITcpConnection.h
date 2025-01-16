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
    void doWrite(ITcpResolver*);

    void doReadFinished();
    void doWriteFinished();
    void doReadError(std::error_code);
    void doWriteError(std::error_code);

private:
    void doWriteImpl();

public:
    std::atomic_bool m_keepAlive{false};
    int m_resolverFactoryId;

private:
    std::mutex m_mutex;
    std::atomic_bool m_error;
    std::atomic_int m_unWrittenCount{0};
    asio::ip::tcp::socket m_socket;
    std::list<ITcpResolver*> m_resolvers;
};

$PackageWebCoreEnd
