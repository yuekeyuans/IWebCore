#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

class ISessionWare;

class ISessionManager : public QObject, public ISingletonUnit<ISessionManager>
{
    Q_OBJECT
public:
    ISessionManager() = default;

public:
    bool isSessionValid();
    void registerSessionWare(ISessionWare*);
    ISessionWare* getSessionWare();

protected:
    virtual void timerEvent(QTimerEvent *event) final;

private:
    int m_timerId{};
    ISessionWare* m_sessionWare{};
};

$PackageWebCoreEnd
