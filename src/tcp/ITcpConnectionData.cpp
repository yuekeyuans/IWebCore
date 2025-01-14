#include "ITcpConnectionData.h"
#include "core/config/IProfileImport.h"

$PackageWebCoreBegin

namespace detail
{
    static IMemoryArrayPool<char> s_pool {};
}

ITcpConnectionData::ITcpConnectionData()
{
    static const $ULong MAX_SIZE{"/http/urlHeaderMaxLength", 1024*10};
    m_data = detail::s_pool.allocateArray(*MAX_SIZE);
}

ITcpConnectionData::~ITcpConnectionData()
{
    static const $ULong MAX_SIZE{"/http/urlHeaderMaxLength", 1024*10};
    detail::s_pool.deallocateArray(m_data, *MAX_SIZE);
}

std::size_t ITcpConnectionData::getLine() const
{
    auto data = std::string_view(m_data + m_parsedSize, m_readSize-m_parsedSize);
    std::size_t pos = data.find("\r\n");
    return (pos == std::string_view::npos) ? 0 : pos+2;
}

std::size_t ITcpConnectionData::getBreakSegment() const
{
    auto data = std::string_view(m_data + m_parsedSize, m_readSize-m_parsedSize);
    std::size_t pos = data.find("\r\n\r\n");
    return (pos == std::string_view::npos) ? 0 : pos+4;
}

std::size_t ITcpConnectionData::getUnparsedLength() const
{
    return m_readSize-m_parsedSize;
}

bool ITcpConnectionData::isDataFull()
{
    return m_readSize == m_maxSize;
}

$PackageWebCoreEnd
