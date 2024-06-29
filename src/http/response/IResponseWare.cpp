#include "IResponseWare.h"

#include "core/util/IConstantUtil.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/response/IRedirectResponse.h"

$PackageWebCoreBegin

IResponseWare::IResponseWare()
    : m_raw(new IResponseRaw())
{
}

IResponseWare::IResponseWare(const IResponseWare &rhs)
    : m_raw(new IResponseRaw(*rhs.m_raw))
{
}

IResponseWare::~IResponseWare()
{
    delete m_raw;
    m_raw = nullptr;
}

IResponseWare::IResponseWare(IResponseWare && rhs)
{
    std::swap(this->m_raw, rhs.m_raw);
}

IResponseWare &IResponseWare::operator =(const IResponseWare & rhs)
{
    delete this->m_raw;
    this->m_raw = new IResponseRaw(*rhs.m_raw);
    return *this;
}

IResponseWare &IResponseWare::operator = (IResponseWare && rhs)
{
    std::swap(this->m_raw, rhs.m_raw);
    return *this;
}

IResponseHeader IResponseWare::operator[](const QString &header)
{
    return IResponseHeader(m_raw, header);
}

const QString& IResponseWare::mime() const
{
    return m_raw->mime;
}

void IResponseWare::setMime(IHttpMime mime)
{
    m_raw->setMime(mime);
}

IHttpStatusCode IResponseWare::status() const
{
    return m_raw->status;
}

void IResponseWare::setStatus(IHttpStatusCode statusCode)
{
    m_raw->status = statusCode;
}

const QMultiHash<QString, QString>& IResponseWare::headers() const
{
    return m_raw->headers;
}

QMultiHash<QString, QString> &IResponseWare::headers()
{
    return m_raw->headers;
}

void IResponseWare::setHeader(const QString &key, const QString &value)
{
    m_raw->headers.insert(key, value);
}

void IResponseWare::addHeader(const QString &key, const QString &value)
{
    m_raw->headers.insertMulti(key, value);
}

IResponseContent &IResponseWare::getContent()
{
    return m_raw->content;
}

QString IResponseWare::getPrefixMatcher()
{
    return {};
}


$PackageWebCoreEnd
