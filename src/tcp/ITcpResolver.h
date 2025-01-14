#pragma once

#include "core/util/IHeaderUtil.h"
#include "ITcpConnectionData.h"

$PackageWebCoreBegin

class ITcpConnection;
class ITcpResolver
{
public:
    enum class ReadState{
        Reading,
        Finished
    };
    enum class WriteState{
        Writing,
        Finished
    };

public:
    ITcpResolver(ITcpConnection& connection, int resolverFactoryId);
    virtual ~ITcpResolver() = default;

public:
    virtual void startRead() = 0;
    virtual void resolve() = 0;
    virtual void startWrite() = 0;
    virtual std::vector<asio::const_buffer> getOutput() = 0;

public:
    ReadState m_readState{ReadState::Finished};
    WriteState m_writeState{WriteState::Finished};
    std::atomic<int> m_writeCount = 1;
    ITcpConnection& m_connection;
    ITcpConnectionData m_data;
    int m_resolverFactoryId;
};

inline ITcpResolver::ITcpResolver(ITcpConnection&  connection, int resolverFactoryId)
    : m_connection(connection), m_resolverFactoryId(resolverFactoryId)
{
}

$PackageWebCoreEnd
