#include "ITcpConnectionManage.h"
#include "http/server/ITcpConnection.h"

$PackageWebCoreBegin

void ITcpConnectionManage::addTcpConnection(ITcpConnection * conn)
{
    std::lock_guard lock(mutex);
    m_connections.emplace(conn);
}

void ITcpConnectionManage::removeTcpConnection(ITcpConnection *conn)
{
    {
        std::lock_guard lock(mutex);
        m_connections.erase(conn);
    }
    delete conn;
}

$PackageWebCoreEnd
