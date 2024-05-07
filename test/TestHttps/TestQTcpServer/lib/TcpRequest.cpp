#include "TcpRequest.h"
#include "ITcpLoopThread.h"

TcpRequest::TcpRequest(qintptr handle, ITcpLoopThread *thread)
    : m_handle(handle), m_socket(new QTcpSocket()), m_thread(thread)
{
    m_socket->setSocketDescriptor(m_handle);
    m_thread->watchRead(m_socket);
}
