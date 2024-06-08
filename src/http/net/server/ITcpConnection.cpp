#include "ITcpConnection.h"
#include "http/net/server/ITcpResolverManage.h"
#include "http/net/server/ITcpResolverInterface.h"
#include "http/net/server/ITcpConnectionManage.h"

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
    m_socket.async_read_some(m_data.getMutableBuffer(), [&](std::error_code error, std::size_t length){
        if(error){
            return doDestroy();
        }

        m_data.m_readSize += length;
        resolveData();
    });
}

void ITcpConnection::doReadStreamBy(int length)
{
    // TODO: 如何在这里保证一个偏移？
    asio::async_read(m_socket, m_data.m_buff, asio::transfer_exactly(length), [=](std::error_code error, std::size_t length){
        if(error){
            return doDestroy();
        }
        resolveData();
    });
}

void ITcpConnection::doReadStreamUntil(const char *stop)
{
    asio::async_read_until(m_socket, m_data.m_buff, stop, [=](std::error_code error, std::size_t length){
        if(error){
            return doDestroy();
        }
        resolveData();
    });
}

void ITcpConnection::doWrite()
{
    auto result = m_resolver->getResult();
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
        m_resolver = ITcpResolverManage::instance()->createResolver(this);
    }

    if(m_resolver){
        m_resolver->resolve();
    }else{
        if(m_data.m_readSize > 4){
            doDestroy();
        }else{
            doRead();
        }
    }
}

$PackageWebCoreEnd
