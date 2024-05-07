#pragma once

#include "core/base/IHeaderUtil.h"

class TcpRequest;
class ITcpLoopThread : public QThread
{
public:
    ITcpLoopThread();

public:
    void addToThread(qintptr handle);
    void watchRead(QTcpSocket* socket);

protected:
    virtual void run() final;

public slots:
    void slotReadyRead();

private:
    QHash<qintptr, TcpRequest*> m_map;
};
