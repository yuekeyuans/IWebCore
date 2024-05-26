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
    m_socket.async_read_some(m_data.getBuffer(), [&](std::error_code error, int length){
        if(error){
            doDestroy();
            return;
        }

        m_data.readSize += length;
        if(!m_resolver){
            m_resolver = ITcpResolverManage::instance()->createResolver(this);
        }

        if(m_resolver){
            m_resolver->resolve();
        }else{
            if(m_data.readSize > 4){
                doDestroy();
            }else{
                doRead();
            }
        }
    });
}

struct TcpData{

};

void ITcpConnection::doWrite()
{
    auto result = m_resolver->getResult();
    qDebug() << result;
    asio::async_write(m_socket, asio::buffer("HTTP/1.1 200 ok\r\n\r\n"), [=](std::error_code err, int){
        if(!m_closeConnection && !err){
            return doReuse();
        }else{
            doDestroy();
        }
    });
}

void ITcpConnection::doDestroy()
{
    asio::post([=](){
        ITcpConnectionManage::instance()->removeTcpConnection(this);
    });
}

void ITcpConnection::doReuse()
{

}


$PackageWebCoreEnd
