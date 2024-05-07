#include "ITcpLoopThread.h"
#include "TcpRequest.h"

ITcpLoopThread::ITcpLoopThread()
{

}

void ITcpLoopThread::addToThread(qintptr handle)
{
    auto request = new TcpRequest(handle, this);
    m_map[handle] = request;
}

void ITcpLoopThread::watchRead(QTcpSocket *socket)
{
    connect(socket, &QTcpSocket::readyRead, this, &ITcpLoopThread::slotReadyRead);
}

void ITcpLoopThread::run()
{
//    while()
}

void ITcpLoopThread::slotReadyRead()
{
    auto socket = dynamic_cast<QTcpSocket*>(sender());
    qDebug() << "read sd" << socket->socketDescriptor();
    qDebug() << "read content" << socket->readAll();
}
