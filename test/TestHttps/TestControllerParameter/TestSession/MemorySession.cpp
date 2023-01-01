#include "MemorySession.h"

MemorySession::MemorySession()
{
    qDebug() << m_sessions.size();
}

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
    m_sessionRing[m_index].insert (id);
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
    const auto index = m_index + IConstantUtil::Session_Expiration;
    for(int i=1; i<IConstantUtil::Session_Expiration; i++){

        int pos = (index - i) % IConstantUtil::Session_Expiration;
        if(m_sessionRing[pos].erase (key)){
            break;
        }
    }

    m_sessionRing[m_index].insert (key);
}
