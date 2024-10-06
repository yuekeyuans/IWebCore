#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/config/IProfileImport.h"

$PackageWebCoreBegin

class IHttpServer
{
public:
    IHttpServer(asio::io_context* context=nullptr);
    ~IHttpServer();

public:
    void listen();

private:
    void doAccept();


private:
    $QString ip{"/http/ip", "0.0.0.0"};
    $Int port{"/http/port", 8550};
    asio::io_context* m_context{};
    asio::ip::tcp::acceptor* m_acceptor{};
};

$PackageWebCoreEnd
