#include "ISessionJar.h"
#include "core/abort/IGlobalAbort.h"
#include "http/IHttpAssert.h"
#include "http/session/ISessionManager.h"
#include "http/session/ISessionInterface.h"
#include "http/net/impl/IRequestRaw.h"

$PackageWebCoreBegin

$UseAssert(IHttpAssert)

ISessionJar::ISessionJar() : IJarUnit(nullptr)
{
    IGlobalAbort::abortUnVisibleMethod();
}

ISessionJar::ISessionJar(IRequestRaw *m_raw) : IJarUnit(m_raw)
{
    m_sessionWare = ISessionManager::instance()->getSessionWare();
    m_sessionId = m_sessionWare->getSessionId(m_raw);
}

bool ISessionJar::isValid() const
{
    return !m_sessionId.isEmpty()
           && m_sessionWare != nullptr && m_sessionWare->isSessionExist(m_sessionId);
}

QVariant ISessionJar::value(const QString key)
{
    return m_sessionWare->getSessionValue (m_sessionId, key);
}

void ISessionJar::setValue(const QString key, QVariant value)
{
    m_sessionWare->setSessionValue (m_sessionId, key, std::move(value));
}

$PackageWebCoreEnd
