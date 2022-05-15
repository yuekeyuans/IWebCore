#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IMultiThreadServer
{
    $UseInstance(IMultiThreadServer)
public:
    IMultiThreadServer() = default;

    static void addSocket(qintptr handle);

private:
    QThreadPool m_pool;
};

$PackageWebCoreEnd
