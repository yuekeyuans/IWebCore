#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IQueneServer
{
public:
    IQueneServer();

private:
    QList<qintptr> m_handles;
};

$PackageWebCoreEnd
