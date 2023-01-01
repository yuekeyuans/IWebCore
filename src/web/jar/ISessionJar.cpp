#include "ISessionJar.h"
#include "web/IWebAssert.h"
#include "web/session/ISessionManager.h"
#include "web/session/ISessionInterface.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

ISessionJar::ISessionJar() : IJarUnit(nullptr)
{
    $Ast->fatal("ISessionJar_CREATE_ERROR");
}

QVariant ISessionJar::value(const QString key)
{
    auto session = ISessionManager::instance ()->getSessionWare();
    return session->getSessionValue (m_sessionId, key);
}

void ISessionJar::setValue(const QString key, QVariant value)
{
    auto session = ISessionManager::instance ()->getSessionWare();
    session->setSessionValue (m_sessionId, key, std::move(value));
}

$PackageWebCoreEnd
