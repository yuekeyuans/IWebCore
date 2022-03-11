#include "IHttpServerManage.h"
#include "server/httpServer/IHttpServerRunable.h"

$PackageWebCoreBegin

void IHttpServerManage::addSocket(qintptr handle)
{
    auto inst = instance();
    auto runable = new IHttpServerRunable(handle);
    inst->pool.start(runable);
}

$PackageWebCoreEnd
