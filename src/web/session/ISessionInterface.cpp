#include "ISessionInterface.h"
#include "web/session/ISessionManager.h"
#include "web/session/ISessionWare.h"

$PackageWebCoreBegin

void ISessionInterfaceProxy::registerSession(void *ptr)
{
    ISessionManager::instance()->registerSessionWare (reinterpret_cast<ISessionWare*>(ptr));
}

$PackageWebCoreEnd
