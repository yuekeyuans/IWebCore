#include "ISessionJar.h"
#include "core/abort/IGlobalAbort.h"
#include "http/session/ISessionManager.h"
#include "http/session/ISessionInterface.h"
#include "http/detail/IRequestRaw.h"
#include "http/detail/IRequestImpl.h"

$PackageWebCoreBegin

ISessionJar::ISessionJar(IRequestImpl& request) : IJarUnit(request)
{
    m_sessionWare = ISessionManager::instance()->getSessionWare();
    m_sessionId = m_sessionWare->getSessionId(&m_impl.m_reqRaw);
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
