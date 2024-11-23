#include "IResponseWare.h"

#include "core/util/IConstantUtil.h"
#include "core/abort/IGlobalAbort.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/response/IRedirectResponse.h"

$PackageWebCoreBegin

IResponseWare::IResponseWare() : m_raw(new IResponseRaw())
{
}

IResponseWare::IResponseWare(const IResponseWare &rhs) : m_raw(new IResponseRaw(*rhs.m_raw))
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
    return IResponseHeader(*m_raw, header);
}

const QString& IResponseWare::mime() const
{
    return m_raw->m_mime;
}

void IResponseWare::setMime(IHttpMime mime)
{
    m_raw->setMime(mime);
}

void IResponseWare::setMime(const QString &mime)
{
    m_raw->setMime(mime);
}

IHttpStatus IResponseWare::status() const
{
    return m_raw->m_status;
}

void IResponseWare::setStatus(IHttpStatus statusCode)
{
    m_raw->m_status = statusCode;
}

const QMultiHash<QString, QString>& IResponseWare::headers() const
{
    return m_raw->m_headers;
}

QMultiHash<QString, QString> &IResponseWare::headers()
{
    return m_raw->m_headers;
}

void IResponseWare::setHeader(const QString &key, const QString &value)
{
    m_raw->m_headers.insert(key, value);
}

void IResponseWare::addHeader(const QString &key, const QString &value)
{
    m_raw->m_headers.insertMulti(key, value);
}

QString IResponseWare::getPrefixMatcher()
{
    return {};
}

IResponseWare IResponseWare::create(const QString &)
{
    IGlobalAbort::abortUnVisibleMethod();
    return {};
}

$PackageWebCoreEnd
