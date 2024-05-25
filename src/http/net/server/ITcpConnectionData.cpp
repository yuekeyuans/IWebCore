#include "ITcpConnectionData.h"

$PackageWebCoreBegin

ITcpConnectionData::ITcpConnectionData()
{
    if(!m_data){
        totalLength = 1024*10;
        m_data = new char[1024*10];
    }
}

ITcpConnectionData::~ITcpConnectionData()
{
    delete []m_data;
}

bool ITcpConnectionData::getLine(int *value) const
{
    value[0] = parsedSize;
    for(int i=parsedSize; i<readSize-1; i++){
        if(m_data[i] == '\r' && m_data[i + 1] == '\n'){     // 这个可以通过 转换类型并 异或 完成数据的判断，更简单一点
            value[1] = i + 2 - parsedSize;
            return true;
        }
    }
    value[1] = parsedSize;
    return false;
}

$PackageWebCoreEnd
