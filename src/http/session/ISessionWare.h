#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IReqRespRaw;
class ISessionWare
{
public:
    ISessionWare() = default;

public:
    virtual QVariant getSessionValue(const QString& sessionId, const QString& key) = 0;
    virtual void setSessionValue(const QString& sessionId, const QString& key, QVariant value) = 0;

    virtual QString createSession() = 0;
    virtual void destroySession(const QString& sessionId) = 0;
    virtual bool isSessionExist(const QString& sessionId) const = 0;

    virtual void updateSession(const QString& key) = 0; // 这个用于 session 更新

    virtual QString getSessionId(IReqRespRaw* raw) const = 0;
};

$PackageWebCoreEnd
