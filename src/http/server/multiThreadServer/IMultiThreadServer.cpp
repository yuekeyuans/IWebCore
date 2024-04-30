#include "IMultiThreadServer.h"
#include "IHttpServerRunnable.h"

$PackageWebCoreBegin

void IMultiThreadServer::addSocket(qintptr handle)
{
    auto inst = instance();
    auto runable = new IHttpServerRunnable(handle);
    inst->m_pool.start(runable);
}

void IMultiThreadServer::addSocket(QTcpSocket *socket)
{
    auto inst = instance();
    auto runable = new IHttpServerRunnable(socket);
    inst->m_pool.start(runable);
}

$PackageWebCoreEnd

