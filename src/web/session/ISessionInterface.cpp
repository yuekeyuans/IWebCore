#include "ISessionInterface.h"
#include "web/session/ISessionManager.h"
#include "web/session/ISessionWare.h"

$PackageWebCoreBegin

void ISessionInterfaceProxy::registerSession(ISessionWare *ptr)
{
    ISessionManager::instance()->registerSessionWare (ptr);
}

$PackageWebCoreEnd
