#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

struct ITcpConnectionData
{
public:
    struct Data{
        Data();
        ~Data();
        void init();

        char* m_data{};
        int totalLength{};
        int readSize{};
        int parsedSize;
    };

public:
    ITcpConnectionData();

public:
    bool getLine(int*) const;
    auto getBuffer(){
        return asio::buffer(m_data + readSize, totalLength - readSize);
    }

public:
    char* m_data{};
    int totalLength{1024*10};
    int readSize{};
    int parsedSize;

    Data m_body;
};

$PackageWebCoreEnd
