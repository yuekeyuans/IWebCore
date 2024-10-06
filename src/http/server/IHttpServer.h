#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IHttpServer
{
public:
    IHttpServer();
    ~IHttpServer();

public:
    void listen();

private:
    void doAccept();

private:
    asio::ip::tcp::acceptor* m_acceptor{};
};

$PackageWebCoreEnd
