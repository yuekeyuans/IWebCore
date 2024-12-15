#include "ITcpConnectionData.h"
#include "core/config/IProfileImport.h"

$PackageWebCoreBegin

ITcpConnectionData::ITcpConnectionData()
{
    static const $Int MAX_SIZE{"/http/urlHeaderMaxLength", 1024*10};

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

bool ITcpConnectionData::getLine(int *value) const
{
    auto data = std::string_view(m_data + m_parsedSize, m_readSize-m_parsedSize);
    std::size_t pos = data.find("\r\n");
    if(pos == std::string_view::npos){
        return false;
    }

    value[0] = m_parsedSize;
    value[1] = pos + 2;
    return true;
}

bool ITcpConnectionData::getBreakSegment(int *value) const
{
    auto data = std::string_view(m_data + m_parsedSize, m_readSize-m_parsedSize);
    std::size_t pos = data.find("\r\n\r\n");
    if(pos == std::string_view::npos){
        return false;
    }

    value[0] = m_parsedSize;
    value[1] = pos + 4;
    return true;
}

void ITcpConnectionData::resetForReuse()
{
    // TODO: do nothing, but clear now;
    // 这个在现在这个条件下似乎没啥必要了，但是，还是写在这里，之后再考虑这件事情
}

$PackageWebCoreEnd
