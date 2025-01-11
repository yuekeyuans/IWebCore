#include "ITcpConnection.h"
#include "core/util/IStringUtil.h"
#include "tcp/ITcpResolver.h"
#include "tcp/ITcpManage.h"

$PackageWebCoreBegin

ITcpConnection::ITcpConnection(asio::ip::tcp::socket&& socket, int resolverFactoryId)
    : m_socket(std::move(socket)), m_resolverFactoryId(resolverFactoryId)
{
}

ITcpConnection::~ITcpConnection()
{
    if(!m_resolvers.empty()){
        qFatal("error");
    }

    if(m_socket.is_open()){
        m_socket.close();
    }
}

void ITcpConnection::doRead()
{
    if(m_resolvers.empty()){
        return;
    }
    m_socket.async_read_some(m_resolvers.back()->m_data.getDataBuffer(), [&](std::error_code error, std::size_t length){
        if(error) {
            return doReadError(error);
        }
        m_resolvers.back()->m_data.m_readSize += length;
        m_resolvers.back()->resolve();
    });
}

void ITcpConnection::doReadStreamBy(int length, bool isData)
{
    if(m_resolvers.empty()){
        return;
    }
    if(isData){
        asio::async_read(m_socket, m_resolvers.back()->m_data.getDataBuffer(), asio::transfer_exactly(length), [&](std::error_code error, std::size_t length){
            if(error){
                return doReadError(error);
            }
            m_resolvers.back()->m_data.m_readSize += length;
            m_resolvers.back()->resolve();
        });
    }else{
        asio::async_read(m_socket, m_resolvers.back()->m_data.m_buffer, asio::transfer_exactly(length), [&](std::error_code error, std::size_t){
            if(error){
                return doReadError(error);
            }
            m_resolvers.back()->resolve();
        });
    }
}

void ITcpConnection::doReadStreamUntil(IStringView data)
{
    asio::async_read_until(m_socket, m_resolvers.back()->m_data.m_buffer, std::string(data), [&](std::error_code error, std::size_t length){
        Q_UNUSED(length)
        if(error){
            return doReadError(error);
        }

        // TODO: 之后看一下
//        if(length > m_resolvers.back()->m_data.m_maxSize - m_resolvers.back()->m_data.m_readSize){
//            return doDestroy();
//        }
        m_resolvers.back()->resolve();
    });
}

void ITcpConnection::doWrite()
{
    if(m_resolvers.front()->m_writeState != ITcpResolver::WriteState::Writing){
        return;
    }

    auto result = m_resolvers.front()->getOutput();
    asio::async_write(m_socket, result, [&](std::error_code err, int){
        if(err){
            return doWriteError(err);
        }
        m_resolvers.front()->m_readState = ITcpResolver::ReadState::Finished;
        m_resolvers.front()->m_writeCount --;
        m_resolvers.front()->resolve();

        // TODO: to be deleted!!!
//        delete m_resolvers.front();
//        m_resolvers.pop();
//        delete this;    // NOTE: this is essential
    });
}

// TODO: 这两个函数中考虑要有一个锁？ 按照道理来说，不会有异常，之后再考虑吧
void ITcpConnection::doReadResolverFinished()
{
    if(m_keepAlive){
        addResolver(ITcpManage::instance()->createResolver(*this, m_resolverFactoryId));
    }
}

void ITcpConnection::doWriteResolverFinished()
{
    delete m_resolvers.front();
    m_resolvers.pop();

    if(!m_resolvers.empty()){
        doWrite();
    }else{
        delete this;
    }
}

void ITcpConnection::doReadError(std::error_code error)
{
    qDebug() << __FUNCTION__;
}

void ITcpConnection::doWriteError(std::error_code error)
{
    qDebug() << __FUNCTION__;
}

//// TODO: this is safe?, but it works
//void ITcpConnection::doDestroy()
//{
////    asio::post([=](){
////    ITcpManage::instance()->removeConnection(this);
////    });
//}

//void ITcpConnection::doReuse()
//{
////    m_data.resetForReuse();
////    delete m_resolver;
////    m_resolver = nullptr;

//    //    resolveData();
//}

void ITcpConnection::addResolver(ITcpResolver *resolver)
{
    m_resolvers.push(resolver);
    resolver->startRead();
}

$PackageWebCoreEnd
