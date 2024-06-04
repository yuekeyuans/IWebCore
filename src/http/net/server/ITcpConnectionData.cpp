#include "ITcpConnectionData.h"
#include "core/config/IProfileImport.h"

$PackageWebCoreBegin

ITcpConnectionData::ITcpConnectionData()
{
    static const $Int MAX_SIZE{"http.urlHeaderMaxLength", 1024*10};

    // TODO: retrive from cache.
    if(!m_data){
        m_maxSize = MAX_SIZE;
        m_data = new char[m_maxSize];
    }
}

ITcpConnectionData::~ITcpConnectionData()
{
    delete []m_data;
}

bool ITcpConnectionData::getLine(int *value) const
{
    value[0] = m_parsedSize;
    for(int i=m_parsedSize; i<m_readSize-1; i++){
        if(m_data[i] == '\r' && m_data[i + 1] == '\n'){     // 这个可以通过 转换类型并 异或 完成数据的判断，更简单一点
            value[1] = i + 2 - m_parsedSize;
            return true;
        }
    }
    value[1] = m_parsedSize;
    return false;
}

void ITcpConnectionData::resetForReuse()
{
    // TODO: do nothing, but clear now;
    // 这个在现在这个条件下似乎没啥必要了，但是，还是写在这里，之后再考虑这件事情
}

$PackageWebCoreEnd
