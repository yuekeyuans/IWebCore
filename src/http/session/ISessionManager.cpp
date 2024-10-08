#include "ISessionManager.h"
#include "ISessionInterface.h"

$PackageWebCoreBegin

bool ISessionManager::isSessionValid()
{
    return m_sessionWare != nullptr;
}

// TODO: 这里的 startTimer 需要改掉
void ISessionManager::registerSessionWare(ISessionWare *sessionWare)
{
    assert(m_sessionWare != sessionWare);

    m_sessionWare = sessionWare;

//    if(m_sessionWare != nullptr){
//        startTimer (60*1000, Qt::TimerType::VeryCoarseTimer);
//    }
}

ISessionWare *ISessionManager::getSessionWare()
{
    return m_sessionWare;
}

//void ISessionManager::timerEvent(QTimerEvent *event)
//{
//    Q_UNUSED (event)
//    if(m_sessionWare == nullptr){
//        killTimer (m_timerId);
//        m_timerId = 0;
//    }
//}

$PackageWebCoreEnd

