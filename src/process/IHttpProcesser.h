#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;

class IHttpProcesser : public QRunnable{

public:
    IHttpProcesser(qintptr handle);
    virtual void run() final;

private:
    bool isSocketAlive(IRequest&);

private:
    qintptr handle{0};
    QTcpSocket* socket{nullptr};
};

$PackageWebCoreEnd
