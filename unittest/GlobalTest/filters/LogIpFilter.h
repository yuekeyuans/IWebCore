#pragma once

#include "tcp/ITcpSocketFilterInterface.h"

using namespace IWebCore;

class LogIpFilter : public ITcpSocketFilterInterface<LogIpFilter>
{
public:
    virtual bool filter(const asio::ip::tcp::socket&) final;
};

