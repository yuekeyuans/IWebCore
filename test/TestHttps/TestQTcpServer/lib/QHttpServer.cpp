#include "QHttpServer.h"
#include "ITcpLoopThread.h"

QHttpServer::QHttpServer()
{
    for(int i=0; i<4; i++){
        m_loop[i] = new ITcpLoopThread;
    }
}

void QHttpServer::listen()
{
    this->QTcpServer::listen(QHostAddress::Any, 8080);
}

void QHttpServer::accept(qintptr handle)
{
    qDebug() << "handle accepted" << handle;
    m_loop[handle %4]->addToThread(handle);
}

void QHttpServer::incomingConnection(qintptr handle)
{
    accept(handle);
}
