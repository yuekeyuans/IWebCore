#pragma once

#include "base/IHeaderUtil.h"
#include "IServerInterface.h"

$PackageWebCoreBegin

class IHttpServerManage
{
public:
    IHttpServerManage();

    void addSocket(qintptr handle);

private:
    QSharedPointer<IServerInterface> m_server;
};

$PackageWebCoreEnd
