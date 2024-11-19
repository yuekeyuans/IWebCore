#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include <unordered_set>

$PackageWebCoreBegin

class ITcpConnection;
class ITcpConnectionManage : public ISingletonUnit<ITcpConnectionManage>
{
public:
    ITcpConnectionManage() = default;

public:
    void addTcpConnection(ITcpConnection*);
    void removeTcpConnection(ITcpConnection*);

private:
    std::mutex mutex;
    std::unordered_set<ITcpConnection*> m_connections;
};

$PackageWebCoreEnd
