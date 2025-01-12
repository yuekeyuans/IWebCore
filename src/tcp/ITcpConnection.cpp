#include "ITcpConnection.h"
#include "core/util/IStringUtil.h"
#include "tcp/ITcpResolver.h"
#include "tcp/ITcpManage.h"
#include <iostream>

$PackageWebCoreBegin

ITcpConnection::ITcpConnection(asio::ip::tcp::socket&& socket, int resolverFactoryId)
    : m_socket(std::move(socket)), m_resolverFactoryId(resolverFactoryId)
{
    qDebug() << __FUNCTION__;
}

ITcpConnection::~ITcpConnection()
{
    if(!m_resolvers.empty()){
        qDebug() << "not empyt";
    }

    qDebug() << __FUNCTION__;
    if(m_socket.is_open()){
        m_socket.close();
    }
}

void ITcpConnection::doRead()
{
    if(m_resolvers.empty()){
        return;
    }

    qDebug() << __FUNCTION__ << m_resolvers.back()->m_index;
    m_socket.async_read_some(m_resolvers.back()->m_data.getDataBuffer(), [&](std::error_code error, std::size_t length){
        if(error) {
            return doReadError(error);
        }
        qDebug() << length;
        m_resolvers.back()->m_data.m_readSize += length;
        m_resolvers.back()->resolve();
    });
}

void ITcpConnection::doReadStreamBy(int length, bool isData)
{
    if(m_resolvers.empty()){
        return;
    }

    static int index{};
    qDebug() << __FUNCTION__ << index ++;

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

    static int index{};
    qDebug() << __FUNCTION__ << index ++;

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

    static unsigned long long lastindex = 1024;
    if(m_resolvers.front()->m_index == lastindex){
        qDebug() << "called last index" << lastindex;
    }
    lastindex = m_resolvers.front()->m_index;

    qDebug() << __FUNCTION__ << m_resolvers.front()->m_index;
    auto result = m_resolvers.front()->getOutput();
    asio::async_write(m_socket, result, [&](std::error_code err, int){
        if(err){
            return doWriteError(err);
        }
        m_resolvers.front()->m_writeCount --;
        m_resolvers.front()->m_readState = ITcpResolver::ReadState::Finished;
        m_resolvers.front()->resolve();
    });
}

void ITcpConnection::doReadFinished()
{
    if(m_keepAlive){
        addResolver(ITcpManage::instance()->createResolver(*this, m_resolverFactoryId));
    }
}

void ITcpConnection::doWriteFinished()
{
    if(!m_resolvers.empty()){
        m_resolvers.deleteFront();
    }

    if(!m_resolvers.empty()){
        qDebug() << "try" << m_resolvers.front()->m_index;
        doWrite();
    }else{
        qDebug() << __FUNCTION__ << "delete" << m_keepAlive << m_resolvers.size();
        delete this;
    }
}

void ITcpConnection::doReadError(std::error_code error)
{
    qDebug() << __FUNCTION__ << error.category().name() << error.value() << QString::fromStdString(error.message());
    m_keepAlive = false;
    if(!m_resolvers.empty()){
        if(m_resolvers.back()->m_data.m_readSize == 0){
            m_resolvers.deleteBack();
        }
    }
    if(m_resolvers.empty()){
        qDebug() << __FUNCTION__ << "delete";
        delete this;
    }
}

void ITcpConnection::doWriteError(std::error_code error)
{
    qDebug() << __FUNCTION__ << error.category().name() << error.value() << QString::fromStdString(error.message());
    Q_UNUSED(error)
//    if(!m_resolvers.empty()){
    m_resolvers.deleteFront();
//    }

    while(!m_resolvers.empty()){
        if(m_resolvers.front()->m_writeState == ITcpResolver::WriteState::Writing){
            if(!m_resolvers.empty()){
                m_resolvers.deleteFront();
//                qDebug() << "clear again";
//                delete m_resolvers.front();
//                m_resolvers.pop_front();
            }
        }else{
            break;
        }
    }
    if(m_resolvers.empty()){
        qDebug() << __FUNCTION__ << "delete";
        delete this;
    }
}

void ITcpConnection::addResolver(ITcpResolver *resolver)
{
    qDebug() << __FUNCTION__ << resolver->m_index;
    m_resolvers.push_back(resolver);
    resolver->startRead();
}

void IResolvers::deleteFront()
{
    ITcpResolver* resolver;
    {
        std::lock_guard lock(m_mutex);
        resolver = this->front();
        this->pop_front();
    }
    qDebug() << __FUNCTION__ << resolver->m_index;
    delete resolver;
}

void IResolvers::deleteBack()
{
    ITcpResolver* resolver;
    {
        std::lock_guard lock(m_mutex);
        resolver = this->back();
        this->pop_back();
    }
    qDebug() << __FUNCTION__ << resolver->m_index;
    delete resolver;
}

void IResolvers::push_back(ITcpResolver *resolver)
{
    std::lock_guard lock(m_mutex);
    std::deque<ITcpResolver*>::push_back(resolver);
}

$PackageWebCoreEnd
