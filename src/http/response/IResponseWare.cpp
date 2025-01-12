#include "IResponseWare.h"

#include "core/util/IConstantUtil.h"
#include "core/abort/IGlobalAbort.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/response/IRedirectResponse.h"

$PackageWebCoreBegin

IResponseWare::IResponseWare() : m_raw(new IResponseRaw())
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

IResponseWare::IResponseWare(const IResponseWare &rhs) : m_raw(new IResponseRaw(*rhs.m_raw))
{
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

//IResponseHeader IResponseWare::operator[](const IString &header)
//{
//    return IResponseHeader(*m_raw, header);
//}

const IString& IResponseWare::mime() const
{
    return m_raw->m_mime;
}

void IResponseWare::setMime(IHttpMime mime)
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

const IHttpHeader& IResponseWare::headers() const
{
    return m_raw->m_headers;
}

IHttpHeader &IResponseWare::headers()
{
    return m_raw->m_headers;
}

void IResponseWare::setHeader(IStringView key, IStringView value)
{
    m_raw->m_headers.insert(key, value);
}

void IResponseWare::setCookie(ICookiePart && cookie)
{
    m_raw->setCookie(std::move(cookie));
}

void IResponseWare::setCookie(const ICookiePart & cookie)
{
    m_raw->setCookie(cookie);
}

void IResponseWare::setCookie(const IString &key, const IString &value)
{
    m_raw->setCookie(key, value);
}

std::string IResponseWare::prefixMatcher()
{
    return {};
}

IResponseWare* IResponseWare::prefixCreate(const std::string &)
{
    IGlobalAbort::abortUnVisibleMethod();
    return nullptr;
}

$PackageWebCoreEnd
