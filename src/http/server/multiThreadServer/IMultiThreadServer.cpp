#include "IMultiThreadServer.h"
#include "IHttpServerRunable.h"

$PackageWebCoreBegin

void IMultiThreadServer::addSocket(qintptr handle)
{
    auto inst = instance();
    auto runable = new IHttpServerRunable(handle);
    inst->m_pool.start(runable);
}

void IMultiThreadServer::addSocket(QTcpSocket *socket)
{
    auto inst = instance();
    auto runable = new IHttpServerRunable(socket);
    inst->m_pool.start(runable);
}

$PackageWebCoreEnd

