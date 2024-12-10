#include "IResponse.h"

#include "core/util/IConstantUtil.h"
#include "core/abort/IGlobalAbort.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/net/IRequest.h"
#include "http/net/impl/IRequestImpl.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/IHeaderJar.h"
#include "http/response/IResponseWare.h"

$PackageWebCoreBegin

IResponse::IResponse(IRequest& request) : m_impl(request.getImpl())
{
}

IResponseHeader IResponse::operator[](const IString &header) const
{
    return {m_impl.m_respRaw, header};
}

IResponse &IResponse::setHeader(IString key, IString value)
{
    m_impl.m_headerJar.setResponseHeader(std::move(key), value);
    return *this;
}

IResponse &IResponse::setStatus(IHttpStatus statusCode)
{
    m_impl.m_respRaw.m_status = statusCode;
    return *this;
}

IResponse &IResponse::setStatus(int statusCode)
{
    m_impl.m_respRaw.m_status = IHttpStatus(statusCode);
    return *this;
}

IResponse &IResponse::setMime(IHttpMime mime)
{
    m_impl.m_respRaw.m_mime = IHttpMimeUtil::toString(mime);
    return *this;
}

IResponse &IResponse::setMime(IString mime)
{
    m_impl.m_respRaw.m_mime = std::move(mime);
    return *this;
}

IResponse &IResponse::addCookie(ICookiePart cookiePart)
{
    m_impl.m_respRaw.m_cookies.push_back(std::move(cookiePart));
    return *this;
}

IResponse &IResponse::setContent(IString && value)
{
    m_impl.m_respRaw.setMime(IHttpMime::TEXT_PLAIN_UTF8);
    m_impl.m_respRaw.setContent(new IResponseContent(std::move(value)));
    return *this;
}

IResponse &IResponse::setContent(const IString & value)
{
    m_impl.m_respRaw.setMime(IHttpMime::TEXT_PLAIN_UTF8);
    m_impl.m_respRaw.setContent(new IResponseContent(value));
    return *this;
}

IResponse &IResponse::setContent(const IResponseWare& ware)
{
    m_impl.setResponseWare(ware);
    return *this;
}

IResponse &IResponse::setContent(const IHttpInvalidWare& unit)
{
    setInvalid(unit);
    return *this;
}

void IResponse::setInvalid(const IHttpInvalidWare& ware)
{
    m_impl.m_isValid = false;
    m_impl.m_respRaw.setContent(ware);
}

IHttpVersion IResponse::version() const
{
    return m_impl.m_reqRaw.m_httpVersion;
}

const IString& IResponse::mime() const
{
    return m_impl.m_respRaw.m_mime;
}

IHttpStatus IResponse::status() const
{
    return m_impl.m_respRaw.m_status;
}

const IHttpHeader& IResponse::headers() const
{
    return m_impl.m_respRaw.m_headers;
}

$PackageWebCoreEnd
