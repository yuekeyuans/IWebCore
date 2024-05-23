#include "ITcpConnection.h"
#include "http/net/server/ITcpResolverManage.h"
#include "http/net/server/ITcpResolverInterface.h"

$PackageWebCoreBegin

ITcpConnection::ITcpConnection(asio::ip::tcp::socket socket)
    : m_socket(std::move(socket))
{
   doRead();
}

void ITcpConnection::doRead(){
    m_socket.async_read_some(m_data.getBuffer(), [&](std::error_code error, int length){
        if(error){
            doDestroy();
        }

        m_data.readSize += length;
        if(!m_resolver){
            m_resolver = ITcpResolverManage::instance()->createResolver(this);
        }

        if(m_resolver){
            m_resolver->resolve();
        }else{
            if(m_data.readSize > 10){
                doDestroy();
            }else{
                doRead();
            }
        }
    });
}

void ITcpConnection::doWrite(){

}

void ITcpConnection::doDestroy(){

}

void ITcpConnection::doReuse(){

}


$PackageWebCoreEnd
