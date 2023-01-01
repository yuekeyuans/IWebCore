#include "MemorySession.h"

MemorySession::MemorySession()
{
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
    m_lock.lockForWrite();
    m_sessions[sessionId][key] = value;
    m_lock.unlock();
}

QString MemorySession::createSession()
{
    auto id = QUuid::createUuid ().toString ();

    m_lock.lockForWrite();
    m_sessions[id] = {};
    m_sessionRing[m_index].insert (id);
    m_lock.unlock();

    return id;
}

void MemorySession::destroySession(const QString &sessionId)
{
    m_lock.lockForWrite();
    m_sessions.erase (sessionId);
    m_lock.unlock();
}

bool MemorySession::isSessionExist(const QString &sessionId)
{
    m_lock.lockForRead();
    return m_sessions.find (sessionId) != m_sessions.end ();
    m_lock.unlock();
}

void MemorySession::updateSession(const QString &key)
{
    m_lock.lockForWrite();
    const auto index = m_index + IConstantUtil::Session_Expiration;
    for(int i=1; i<IConstantUtil::Session_Expiration; i++){

        int pos = (index - i) % IConstantUtil::Session_Expiration;
        if(m_sessionRing[pos].erase (key)){
            break;
        }
    }

    m_sessionRing[m_index].insert (key);
    m_lock.unlock();
}
