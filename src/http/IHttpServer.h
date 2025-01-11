#pragma once

#include "tcp/ITcpServer.h"

class IHttpServer : public ITcpServer
{
public:
    IHttpServer(asio::io_context* context=nullptr);
};

