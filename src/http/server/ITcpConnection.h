﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/server/ITcpConnectionData.h"

$PackageWebCoreBegin

class ITcpResolverInterface;

class ITcpConnection
{
    friend class ITcpResolverInterface;
public:
    ITcpConnection(asio::ip::tcp::socket socket);
    virtual ~ITcpConnection();

public:
    void doRead();
    void doReadStreamBy(int length, bool isData = true);
    void doReadStreamUntil(IStringView, bool isData = true);
    void doWrite();
    void doDestroy();
    void doReuse();

private:
    void resolveData();

public:
    ITcpConnectionData m_data;

private:
    asio::ip::tcp::socket m_socket;
    ITcpResolverInterface* m_resolver{};
    bool m_closeConnection{true};
};

$PackageWebCoreEnd
