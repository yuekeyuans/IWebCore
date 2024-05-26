#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

struct ITcpConnectionData
{
public:
    ITcpConnectionData();
    ~ITcpConnectionData();
public:
    bool getLine(int*) const;
    auto getBuffer(){
        return asio::buffer(m_data + readSize, totalLength - readSize);
    }

public:
    char* m_data{};
    int totalLength{1024*10};
    int readSize{};
    int parsedSize{};
};

$PackageWebCoreEnd
