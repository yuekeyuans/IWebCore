#include "IHttpServerManage.h"
#include "common/server/multiThreadServer/IMultiThreadServer.h"

$PackageWebCoreBegin

IHttpServerManage::IHttpServerManage()
{
    m_server = QSharedPointer<IMultiThreadServer>::create();
}

void IHttpServerManage::addSocket(qintptr handle)
{
    m_server->addSocket(handle);
}

$PackageWebCoreEnd
