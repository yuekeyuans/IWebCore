#include "ITcpResolver.h"

$PackageWebCoreBegin

ITcpResolver::ITcpResolver(ITcpConnection&  connection)
    : m_connection(connection)
{
    static unsigned long long index{};
    m_index = index ++;
    qDebug() << __FUNCTION__ << m_index;
}

$PackageWebCoreEnd
