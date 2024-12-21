#pragma once

#include "core/util/IHeaderUtil.h"

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
    bool getBreakSegment(int*) const;
    void resetForReuse();

public:
    char* m_data{};
    uint m_maxSize{1024*10};
    uint m_readSize{};
    uint m_parsedSize{};

public:
    asio::streambuf m_buffer; // 存储超过请求的内容，这个表示额外的内容
};

$PackageWebCoreEnd
