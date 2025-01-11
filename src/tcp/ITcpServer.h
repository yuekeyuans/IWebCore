#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/config/IProfileImport.h"

$PackageWebCoreBegin

class ITcpServer
{
public:
    ITcpServer(asio::io_context* context=nullptr);
    virtual ~ITcpServer();

public:
    void listen();

private:
    void loadResolverFactory();
    void doAccept();

protected:
    std::string m_ip{};
    int m_port{};
    int m_resolverFactoryId{-1};
    asio::io_context* m_context{};
    asio::ip::tcp::acceptor* m_acceptor{};
};

$PackageWebCoreEnd
