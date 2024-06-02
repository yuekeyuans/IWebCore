#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IProfileImport.h"

$PackageWebCoreBegin

class ITcpConnection;
class IHttpServer
{
public:
    IHttpServer() = default;
    void listen();

private:
    void doAccept();

private:
    $QString ip{"", "0.0.0.0"};
    $Int port{"", 8550};
    asio::ip::tcp::acceptor* m_acceptor{};
};

$PackageWebCoreEnd
