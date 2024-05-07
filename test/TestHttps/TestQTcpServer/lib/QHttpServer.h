#pragma once

#include "core/base/IHeaderUtil.h"
#include "ITcpServerInterface.h"
#include <array>

class ITcpLoopThread;
class QHttpServer : public ITcpServerInterface, public QTcpServer
{
public:
    QHttpServer();
    void listen();

public:
    virtual void accept(qintptr handle) final;

private:
    void incomingConnection(qintptr handle);
    std::array<ITcpLoopThread*, 4> m_loop{};
};


