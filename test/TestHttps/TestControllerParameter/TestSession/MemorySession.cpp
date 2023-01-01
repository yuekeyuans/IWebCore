#include "MemorySession.h"

QVariant MemorySession::getSessionValue(const QString &sessionId, const QString &key)
{
    const auto& map = m_sessions[sessionId];
    if(map.contains (key)){
        return map[key];
    }
    return {};
}

void MemorySession::setSessionValue(const QString &sessionId, const QString &key, QVariant value)
{
    m_sessions[sessionId][key] = value;
}

QString MemorySession::createSession()
{
    auto id = QUuid::createUuid ().toString ();
    m_sessions[id] = {};
    return id;
}

void MemorySession::destroySession(const QString &sessionId)
{
    m_sessions.erase (sessionId);
}

bool MemorySession::isSessionExist(const QString &sessionId)
{
    return m_sessions.find (sessionId) != m_sessions.end ();
}

void MemorySession::updateSession(const QString &key)
{
    qFatal("not impliment");
}
