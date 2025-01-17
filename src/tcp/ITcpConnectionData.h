#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

struct ITcpConnectionData
{
public:
    ITcpConnectionData();
    ~ITcpConnectionData();
public:
    auto getDataBuffer(){
        return asio::buffer(m_data + m_readSize, m_maxSize - m_readSize);
    }

    std::size_t getLine() const;
    std::size_t getBreakSegment() const;
    std::size_t getUnparsedLength() const;
    bool isDataFull();

public:
    char* m_data{};
    bool m_bodyInData{true};    // 表示数据存放在 data 上面
    std::size_t m_maxSize{1024*10};
    std::size_t m_readSize{};
    std::size_t m_parsedSize{};

public:
    asio::streambuf m_buffer; // 存储超过请求的内容，这个表示额外的内容
};

$PackageWebCoreEnd
