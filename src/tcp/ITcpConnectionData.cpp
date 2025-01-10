#include "ITcpConnectionData.h"
#include "core/config/IProfileImport.h"

$PackageWebCoreBegin

ITcpConnectionData::ITcpConnectionData()
{
    static const $ULong MAX_SIZE{"/http/urlHeaderMaxLength", 1024*10};

    // TODO: retrive from cache.
    if(!m_data){
        m_maxSize = *MAX_SIZE;
        m_data = new char[m_maxSize];
    }
}

ITcpConnectionData::~ITcpConnectionData()
{
    delete []m_data;
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

void ITcpConnectionData::resetForReuse()
{
    // TODO: do nothing, but clear now;
    // 这个在现在这个条件下似乎没啥必要了，但是，还是写在这里，之后再考虑这件事情
}

$PackageWebCoreEnd
