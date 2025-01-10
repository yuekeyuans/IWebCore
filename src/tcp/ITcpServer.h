#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/config/IProfileImport.h"

$PackageWebCoreBegin

class ITcpServer
{
public:
    ITcpServer(asio::io_context* context=nullptr);
    ~ITcpServer();

public:
    void listen();

private:
    void doAccept();

private:
    $QString ip{"/http/ip", "0.0.0.0"};
    $Int port{"/http/port", 8550};
    int m_resolverFactoryId{};
    asio::io_context* m_context{};
    asio::ip::tcp::acceptor* m_acceptor{};

};

$PackageWebCoreEnd
