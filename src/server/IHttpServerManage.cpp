#include "IHttpServerManage.h"
#include "server/httpServer/IHttpServerRunable.h"

#include "server/httpServer/IMultiThreadServer.h"

$PackageWebCoreBegin

void IHttpServerManage::addSocket(qintptr handle)
{
    IMultiThreadServer::addSocket(handle);
//#ifdef _MSC_VER

//#else

//#endif
}

$PackageWebCoreEnd
