#include "IHttpServerManage.h"
#include "web/server/multiThreadServer/IMultiThreadServer.h"

$PackageWebCoreBegin

const char* MasterServer = "MasterServer";

IHttpServerManage::IHttpServerManage()
{
    m_server = QSharedPointer<IMultiThreadServer>::create();
}

void IHttpServerManage::addSocket(qintptr handle)
{
    auto inst = instance();
    inst->m_server->addSocket(handle);
}

void IHttpServerManage::addSocket(QTcpSocket *socket)
{
    auto inst = instance();
    inst->m_server->addSocket(socket);
}

$PackageWebCoreEnd
