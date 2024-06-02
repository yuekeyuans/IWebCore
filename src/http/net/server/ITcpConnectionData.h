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
    void resetForReuse();

public:
    char* m_data{};
    int totalLength{1024*10};
    int readSize{};
    int parsedSize{};
};

struct MyBuffer
{
    MyBuffer(QByteArray array){
        m_array = array;
    }

    char* data(){
        return m_array.data();
    }

    std::size_t size(){
        return m_array.length();
    }

    MyBuffer operator +=(int n){
        return MyBuffer(m_array.mid(n));
    }

private:
    QByteArray m_array;
};

struct IResultData
{
    using iterator = const std::vector<MyBuffer>::const_iterator;

    iterator begin() const {
        return m_buffer.begin();
    }

    iterator end() const{
        return m_buffer.end();
    }

private:
    std::vector<MyBuffer> m_buffer;
};

$PackageWebCoreEnd
