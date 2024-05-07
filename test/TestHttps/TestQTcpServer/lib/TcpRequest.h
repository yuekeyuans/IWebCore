#pragma once

#include "core/base/IHeaderUtil.h"
#include "lib/ITcpReceiverInterface.h"

class ITcpLoopThread;
class TcpRequest : public ITcpReceiverInterface
{
public:
    TcpRequest(qintptr handle, ITcpLoopThread* thread);

public:
    qintptr m_handle{};
    QTcpSocket* m_socket{};
    ITcpLoopThread* m_thread;
};

