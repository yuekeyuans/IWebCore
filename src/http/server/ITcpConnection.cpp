﻿#include "ITcpConnection.h"
#include "core/util/IStringUtil.h"
#include "http/server/ITcpResolverManage.h"
#include "http/server/ITcpResolverInterface.h"
#include "http/server/ITcpConnectionManage.h"

$PackageWebCoreBegin

ITcpConnection::ITcpConnection(asio::ip::tcp::socket socket)
    : m_socket(std::move(socket))
{
    doRead();
}

ITcpConnection::~ITcpConnection()
{
    if(m_socket.is_open()){
        m_socket.close();
    }
    delete m_resolver;
}

void ITcpConnection::doRead()
{
    m_socket.async_read_some(m_data.getDataBuffer(), [&](std::error_code error, std::size_t length){
        if(error) {
            return doDestroy();
        }
        m_data.m_readSize += length;
        resolveData();
    });
}

void ITcpConnection::doReadStreamBy(int length, bool isData)
{
    if(isData){
        asio::async_read(m_socket, m_data.getDataBuffer(), asio::transfer_exactly(length), [&](std::error_code error, std::size_t length){
            if(error){
                return doDestroy();
            }
            m_data.m_readSize += length;
            resolveData();
        });
    }else{
        asio::async_read(m_socket, m_data.m_buffer, asio::transfer_exactly(length), [&](std::error_code error, std::size_t){
            if(error){
                return doDestroy();
            }
            resolveData();
        });
    }
}

void ITcpConnection::doReadStreamUntil(IStringView data, bool isData)
{
    if(isData){
        asio::async_read_until(m_socket, m_data.m_buffer, std::string(data), [&](std::error_code error, std::size_t length){
            if(error){
                return doDestroy();
            }

            if(length > m_data.m_maxSize - m_data.m_readSize){
                return doDestroy();
            }
            m_data.m_buffer.consume(m_data.m_buffer.size());
            memcpy(m_data.m_data, m_data.m_buffer.data().data(), length);
            m_data.m_readSize += length;
            resolveData();
        });
    }else{
        asio::async_read_until(m_socket, m_data.m_buffer, std::string(data), [&](std::error_code error, std::size_t){
            if(error){
                return doDestroy();
            }
            resolveData();
        });
    }
}

void ITcpConnection::doWrite()
{
    auto result = m_resolver->getOutput();
    asio::async_write(m_socket, result, [=](std::error_code err, int){
        if(!m_closeConnection && !err){
            return doReuse();
        }else{
            doDestroy();
        }
    });
}

// TODO: this is safe?, but it works
void ITcpConnection::doDestroy()
{
//    asio::post([=](){
    ITcpConnectionManage::instance()->removeTcpConnection(this);
//    });
}

void ITcpConnection::doReuse()
{
    m_data.resetForReuse();
    delete m_resolver;
    m_resolver = nullptr;

    resolveData();
}

void ITcpConnection::resolveData()
{
    if(!m_resolver){
        m_resolver = ITcpResolverManage::instance()->createResolver(*this);
    }
    m_resolver->resolve();
}

$PackageWebCoreEnd
