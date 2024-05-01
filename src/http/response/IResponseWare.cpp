#include "IResponseWare.h"

#include "core/base/IConstantUtil.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/response/IRedirectResponse.h"
#include "http/IHttpAssert.h"

$PackageWebCoreBegin

$UseAssert(IHttpAssert)

IResponseWare::IResponseWare()
    : m_raw(new IResponseRaw())
{
}

IResponseWare::~IResponseWare()
{
    delete m_raw;
    m_raw = nullptr;
}

IResponseWare::IResponseWare(const IResponseWare &rhs)
    : m_raw(new IResponseRaw(*rhs.m_raw))
{
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

IResponseWare &IResponseWare::operator =(IResponseWare && rhs)
{
    std::swap(this->m_raw, rhs.m_raw);
    return *this;
}

IResponseHeaderRef IResponseWare::operator[](const QString &header)
{
    auto value = m_raw->headers.value(header);
    return IResponseHeaderRef(m_raw, header, value);
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

void IResponseWare::setHeader(const QString &key, const QString &value)
{
    if(key.isEmpty() || value.isEmpty()){
        $Ast->fatal("iresponse_setHeader_with_empty_value_or_key");
        return;
    }
    m_raw->headers.insert(key, value);
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
