#include "ITcpConnection.h"
#include "core/util/IStringUtil.h"
#include "tcp/ITcpResolver.h"
#include "tcp/ITcpManage.h"
#include <iostream>

$PackageWebCoreBegin

ITcpConnection::ITcpConnection(asio::ip::tcp::socket&& socket, int resolverFactoryId)
    : m_socket(std::move(socket)), m_resolverFactoryId(resolverFactoryId)
{
    auto resolver = ITcpManage::instance()->createResolver(*this, m_resolverFactoryId);
    m_resolvers.push_back(resolver);
    resolver->startRead();
}

ITcpConnection::~ITcpConnection()
{
    if(m_socket.is_open()){
        m_socket.close();
    }
}

void ITcpConnection::doRead()
{
    m_socket.async_read_some(m_resolvers.back()->m_data.getDataBuffer(), [&](std::error_code error, std::size_t length){
        if(error) {
            return doReadError(error);
        }

        auto back = m_resolvers.back();
        back->m_data.m_readSize += length;
        back->resolve();
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

void ITcpConnection::doWrite(ITcpResolver* resolver)
{
    if(m_resolvers.front() != resolver){
        m_unWrittenCount ++;
        return;
    }

    doWriteImpl();
}

void ITcpConnection::doReadFinished()
{
    if(m_keepAlive){
        auto resolver = ITcpManage::instance()->createResolver(*this, m_resolverFactoryId);
        m_resolvers.push_back(resolver);
        resolver->startRead();
    }
}

void ITcpConnection::doWriteFinished()
{
    auto front = m_resolvers.front();
    m_resolvers.pop_front();
    delete front;

    if(m_unWrittenCount != 0){
        if(m_resolvers.front()->m_writeState == ITcpResolver::WriteState::Writing){
            m_unWrittenCount --;
            doWriteImpl();
        }
    }

    if(m_resolvers.empty()){
        delete this;
    }
}

void ITcpConnection::doReadError(std::error_code error)
{
    Q_UNUSED(error);

    m_keepAlive = false;
    if(m_resolvers.back()->m_readState == ITcpResolver::ReadState::Finished){       // 说明这个还没读取， 只删除没有读取的。
        auto back = m_resolvers.back();
        m_resolvers.pop_back();
        delete back;
    }

    if(m_resolvers.empty()){
        delete this;
    }
}

void ITcpConnection::doWriteError(std::error_code error)
{
    Q_UNUSED(error)
    auto front = m_resolvers.front();
    m_resolvers.pop_front();
    delete front;

    if(m_unWrittenCount != 0 && m_resolvers.front()->m_writeState == ITcpResolver::WriteState::Writing){
        m_unWrittenCount --;
        doWriteImpl();
    }

    if(m_resolvers.empty()){
        delete this;
    }
}

void ITcpConnection::doWriteImpl()
{
    auto result = m_resolvers.front()->getOutput();
    asio::async_write(m_socket, result, [&](std::error_code err, int){
        if(err){
            return doWriteError(err);
        }
        m_resolvers.front()->m_writeCount --;
        m_resolvers.front()->m_writeState = ITcpResolver::WriteState::Finished;
        m_resolvers.front()->resolve();
    });
}

$PackageWebCoreEnd
