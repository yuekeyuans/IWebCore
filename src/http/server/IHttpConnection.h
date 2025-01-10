#pragma once

#include "tcp/ITcpConnection.h"

$PackageWebCoreBegin

class IHttpConnection : public ITcpConnection
{
public:
    using ITcpConnection::ITcpConnection;
};

$PackageWebCoreEnd
