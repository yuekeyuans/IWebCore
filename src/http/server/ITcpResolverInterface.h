﻿#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class ITcpConnection;
class ITcpResolverInterface
{
protected:

public:
    ITcpResolverInterface(ITcpConnection* connection);
   virtual ~ITcpResolverInterface() = default;

public:
    virtual void resolve() = 0;
    virtual std::vector<asio::const_buffer> getResult() = 0;

public:
    ITcpConnection* m_connection{};
};

$PackageWebCoreEnd
