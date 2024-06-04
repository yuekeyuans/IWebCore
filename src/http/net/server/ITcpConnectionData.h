#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

struct ITcpConnectionData
{
public:
    ITcpConnectionData();
    ~ITcpConnectionData();
public:
    auto getMutableBuffer(){
        return asio::buffer(m_data + m_readSize, m_maxSize - m_readSize);
    }

    bool getLine(int*) const;
    void resetForReuse();

public:
    char* m_data{};
    int m_maxSize{1024*10};
    int m_readSize{};
    int m_parsedSize{};

public:
    asio::streambuf m_buff; // 存储超过请求的内容，这个表示额外的内容
};

$PackageWebCoreEnd
