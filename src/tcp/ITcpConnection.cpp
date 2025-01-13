#include "ITcpConnection.h"
#include "core/util/IStringUtil.h"
#include "tcp/ITcpResolver.h"
#include "tcp/ITcpManage.h"
#include <iostream>

$PackageWebCoreBegin

ITcpConnection::ITcpConnection(asio::ip::tcp::socket&& socket, int resolverFactoryId)
    : m_socket(std::move(socket)), m_resolverFactoryId(resolverFactoryId)
{
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

    static int index{};
    //  qDebug() << __FUNCTION__ << index ++;

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
    //  qDebug() << __FUNCTION__ << index ++;

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
        qDebug() << "increase" << m_unWrittenCount;
        return;
    }

    doWriteImpl();
}

void ITcpConnection::doReadFinished()
{
    if(m_keepAlive){
        addResolver(ITcpManage::instance()->createResolver(*this, m_resolverFactoryId));
    }
}

void ITcpConnection::doWriteFinished()
{
    if(m_resolvers.empty()){
        qFatal("error");
    }

    m_resolvers.deleteFront();
    if(m_unWrittenCount != 0){
        if(m_resolvers.front()->m_writeState == ITcpResolver::WriteState::Writing){
            m_unWrittenCount --;
            qDebug() << "decrease" << m_unWrittenCount;
            doWriteImpl();
        }
    }
    if(m_resolvers.empty()){
        delete this;
    }
}

// TODO: 这里有可能读取和写入错误同时发生，因为程序正在读取，也正在写入，他们一同出错
void ITcpConnection::doReadError(std::error_code error)
{
    std::lock_guard lock(m_mutex);

    m_keepAlive = false;

    if(m_resolvers.back()->m_readState == ITcpResolver::ReadState::Finished)
    m_resolvers.deleteBack();

    if(m_resolvers.empty()){
        delete this;
    }
}

void ITcpConnection::doWriteError(std::error_code error)
{
    qDebug() << __FUNCTION__;
    //  qDebug() << __FUNCTION__ << error.category().name() << error.value() << QString::fromStdString(error.message());
    Q_UNUSED(error)
    if(m_resolvers.empty()){
        qFatal("error");
    }
    m_resolvers.deleteFront();

//    if(!m_resolvers.empty()){
//        m_resolvers.back()->m_readState == ITcpResolver::ReadState::
//    }



//    while(!m_resolvers.empty()){
//        if(m_resolvers.front()->m_wri
//                teState == ITcpResolver::WriteState::Writing){
//            if(!m_resolvers.empty()){
//                m_resolvers.deleteFront();
////                //  qDebug() << "clear again";
////                delete m_resolvers.front();
////                m_resolvers.pop_front();
//            }
//        }else{
//            break;
//        }
//    }
    if(m_resolvers.empty()){
        //  qDebug() << __FUNCTION__ << "delete";
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

void ITcpConnection::addResolver(ITcpResolver *resolver)
{
    //  qDebug() << __FUNCTION__ << resolver->m_index;
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
        if(size() == 0){
            qDebug() << __FUNCTION__;
        }
    }
    delete resolver;
}

void IResolvers::deleteBack()
{
    ITcpResolver* resolver;
    {
        std::lock_guard lock(m_mutex);
        resolver = this->back();
        this->pop_back();
        if(size() == 0){
            qDebug() << __FUNCTION__;
        }
    }
    delete resolver;
}

void IResolvers::push_back(ITcpResolver *resolver)
{
    std::lock_guard lock(m_mutex);
    std::list<ITcpResolver*>::push_back(resolver);
}

$PackageWebCoreEnd
