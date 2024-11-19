#include "ISessionInterface.h"
#include "http/session/ISessionManager.h"
#include "http/session/ISessionWare.h"

$PackageWebCoreBegin

void ISessionInterfaceProxy::registerSession(ISessionWare *ptr)
{
    ISessionManager::instance()->registerSessionWare (ptr);
}

$PackageWebCoreEnd
