#pragma once

#include <IWebCore>
#include "web/session/ISessionInterface.h"
#include "unordered_map"
#include "set"

class MemorySession : public ISessionInterface<MemorySession, true>
{
    Q_GADGET
    $UseInstance (MemorySession)
public:
    MemorySession();

public:
    virtual QVariant getSessionValue(const QString& sessionId, const QString& key) final;
    virtual void setSessionValue(const QString& sessionId, const QString& key, QVariant value) final;

    virtual QString createSession() final;
    virtual void destroySession(const QString& sessionId) final;
    virtual bool isSessionExist(const QString& sessionId) const final;
    virtual void updateSession(const QString& key) final;
    virtual QString getSessionId(IReqRespRaw*) const final;

private:
    std::unordered_map<QString, QMap<QString, QVariant>> m_sessions{};
    std::array<std::set<QString>, IConstantUtil::Session_Expiration> m_sessionRing{};
    int m_index{0};

    mutable QReadWriteLock m_lock;
};

