#include "ITcpResolver.h"

$PackageWebCoreBegin

ITcpResolver::ITcpResolver(ITcpConnection&  connection)
    : m_connection(connection)
{
    static std::atomic<std::uint64_t> index{};
    m_index = index ++;
//    qDebug() << __FUNCTION__ << m_index;
}

$PackageWebCoreEnd
