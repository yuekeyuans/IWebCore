#include "IRequest.h"

#include "core/abort/IGlobalAbort.h"
#include "core/unit/IObjectMemoryPoolUnit.h"
#include "http/action/IHttpAction.h"
#include "http/detail/IRequestImpl.h"
#include "http/ICookieJar.h"
#include "http/ISessionJar.h"
#include "http/IHeaderJar.h"
#include "tcp/ITcpConnection.h"

$PackageWebCoreBegin

namespace detail
{
    static IObjectMemoryPoolUnit<IRequestImpl> s_pool;
}

IRequest::IRequest(ITcpConnection& connection, int resolverFactoryId)
    : ITcpResolver(connection, resolverFactoryId)
{
    m_impl = detail::s_pool.allocate(*this);
}

IRequest::~IRequest()
{
    detail::s_pool.deallocate(m_impl);
}

IStringView IRequest::operator[](const IString &header) const
{
    return m_impl->m_headerJar.getRequestHeaderValue(header);
}

IStringView IRequest::operator[](const QString &header) const
{
    return m_impl->m_headerJar.getRequestHeaderValue(header.toUtf8());
}

const ICookieJar& IRequest::cookieJar() const
{
    return m_impl->m_cookieJar;
}

const ISessionJar& IRequest::sessionJar() const
{
    if(!m_impl->m_sessionJar){
        qFatal("error, session not configured");
    }
    return *m_impl->m_sessionJar;
}

const IHeaderJar& IRequest::headerJar() const
{
    return m_impl->m_headerJar;
}

const IMultiPartJar& IRequest::multiPartJar() const
{
    return m_impl->m_multiPartJar;
}

IRequestImpl& IRequest::impl() const
{
    return *m_impl;
}

IStringView IRequest::url() const
{
    return m_impl->m_reqRaw.m_url;
}

IHttpVersion IRequest::version() const
{
    return m_impl->m_reqRaw.m_httpVersion;
}

IHttpMime IRequest::mime() const
{
    return m_impl->m_reqRaw.m_mime;
}

IHttpMethod IRequest::method() const
{
    return m_impl->m_reqRaw.m_method;
}

int IRequest::contentLength() const
{
    return m_impl->m_reqRaw.m_contentLength;
}

IStringView IRequest::contentType() const
{
    return m_impl->m_headerJar.getRequestHeaderValue(IHttpHeader::ContentType);
}

IStringView IRequest::content() const
{
    return m_impl->m_reqRaw.m_body;
}

const QMap<IStringView, IStringView> &IRequest::pathParameters() const
{
    return m_impl->m_reqRaw.m_paths;
}

const QMap<IStringView, IStringView> &IRequest::queryParameters() const
{
    return m_impl->m_reqRaw.m_queries;
}

const QMap<IStringView, IStringView> &IRequest::bodyFormParameters() const
{
    return m_impl->m_reqRaw.m_forms;
}

const std::vector<IMultiPart> &IRequest::bodyMultiParts() const
{
    return m_impl->m_reqRaw.m_multiParts;
}

const IJson& IRequest::bodyJson() const
{
    return m_impl->m_reqRaw.m_json;
}

IStringView IRequest::stash(const char *data)
{
    return m_impl->stash(data);
}

IStringView IRequest::stash(QByteArray &&data)
{
    return m_impl->stash(std::move(data));
}

IStringView IRequest::stash(const QByteArray &data)
{
    return m_impl->stash(data);
}

IStringView IRequest::stash(const QString &data)
{
    return m_impl->stash(data);
}

IStringView IRequest::stash(std::string &&data)
{
    return m_impl->stash(std::move(data));
}

IStringView IRequest::stash(const std::string &data)
{
    return m_impl->stash(data);
}

IStringView IRequest::stash(IString &&data)
{
    return m_impl->stash(std::move(data));
}

IStringView IRequest::stash(const IString &data)
{
    return m_impl->stash(data);
}

IStringView IRequest::stash(IStringView data)
{
    return m_impl->stash(data);
}

bool IRequest::isValid() const
{
    return m_impl->m_isValid;
}

void IRequest::setInvalidIf(bool condition, IHttpInvalidWare ware) const
{
    if(condition){
        setInvalid(ware);
    }
}

void IRequest::setInvalid(const IHttpInvalidWare& ware) const
{
    m_impl->setInvalid(ware);
}

void IRequest::startRead()
{
    m_readState = ReadState::Reading;
    m_connection.doRead();
}

void IRequest::resolve()
{
    if(m_writeCount == 0){
        m_connection.doWriteFinished();
        return;
    }
    m_impl->parseData();
}

void IRequest::startWrite()
{
    m_writeState = WriteState::Writing;
    m_connection.doWrite(this);
}

std::vector<asio::const_buffer> IRequest::getOutput()
{
    return m_impl->m_respRaw.getContent(*(this->m_impl));
}

$PackageWebCoreEnd
