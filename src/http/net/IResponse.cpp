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

IResponse::IResponse() : m_impl(*static_cast<IRequestImpl*>(nullptr))
{
    IGlobalAbort::abortUnVisibleMethod();
}

IResponse::IResponse(IRequest& request) : m_impl(request.getImpl())
{
}

IResponse::IResponse(const IResponse &) : m_impl(*static_cast<IRequestImpl*>(nullptr))
{
    IGlobalAbort::abortUnVisibleMethod();
}

IResponse::IResponse(IResponse &&) : m_impl(*static_cast<IRequestImpl*>(nullptr))
{
    IGlobalAbort::abortUnVisibleMethod();
}

IResponse &IResponse::operator=(const IResponse &)
{
    IGlobalAbort::abortUnVisibleMethod();
    return *this;
}

IResponse &IResponse::operator=(IResponse &&)
{
    IGlobalAbort::abortUnVisibleMethod();
    return *this;
}

IResponseHeader IResponse::operator[](const QString &header) const
{
    return {m_impl.m_respRaw, header};
}

IResponse &IResponse::setHeader(const QString &key, const QString &value)
{
    m_impl.m_headerJar.setResponseHeader(key, value);
    return *this;
}

IResponse &IResponse::setStatus(IHttpStatus statusCode)
{
    m_impl.m_respRaw.m_status = statusCode;
    return *this;
}

IResponse &IResponse::setStatus(int statusCode)
{
    m_impl.m_respRaw.m_status = IHttpStatusUtil::toStatus(statusCode);
    return *this;
}

IResponse &IResponse::setMime(IHttpMime mime)
{
    m_impl.m_respRaw.m_mime = IHttpMimeUtil::toString(mime);
    return *this;
}

IResponse &IResponse::setMime(const QString mime)
{
    m_impl.m_respRaw.m_mime = mime;
    return *this;
}

IResponse &IResponse::addCookie(ICookiePart cookiePart)
{
    m_impl.m_respRaw.m_cookies.push_back(std::move(cookiePart));
    return *this;
}

IResponse &IResponse::setContent(std::string && value)
{
    m_impl.m_respRaw.setContent(std::move(value));
    return *this;
}

IResponse &IResponse::setContent(const std::string &value)
{
    m_impl.m_respRaw.setContent(value);
    return *this;
}

IResponse &IResponse::setContent(IStringView view)
{
    m_impl.m_respRaw.setContent(view);
    return *this;
}

IResponse &IResponse::setContent(QString && value)
{
    m_impl.m_respRaw.setContent(std::move(value));
    return *this;
}

IResponse &IResponse::setContent(const QString &content)
{
    m_impl.m_respRaw.setContent(content);
    return *this;
}

IResponse &IResponse::setContent(const QByteArray &content)
{
    m_impl.m_respRaw.setContent(content);
    return *this;
}

IResponse &IResponse::setContent(QByteArray &&content)
{
    m_impl.m_respRaw.setContent(std::move(content));
    return *this;
}

IResponse &IResponse::setContent(const char *content)
{
    m_impl.m_respRaw.setContent(content);
    return *this;
}

IResponse &IResponse::setContent(IResponseWare& ware)
{
    m_impl.setResponseWare(ware);
    return *this;
}

IResponse &IResponse::setContent(IResponseWare &&ware)
{
    m_impl.setResponseWare(std::move(ware));
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

const IStringData& IResponse::mime() const
{
    return m_impl.m_respRaw.m_mime;
}

IHttpStatus IResponse::status() const
{
    return m_impl.m_respRaw.m_status;
}

const QMultiHash<QString, QString>& IResponse::headers() const
{
    return m_impl.m_respRaw.m_headers;
}

const QMap<QString, QVariant> &IResponse::attributes() const
{
    return m_impl.m_attribute;
}

bool IResponse::hasAttribute(const QString &name) const
{
    return m_impl.m_attribute.contains(name);
}

void IResponse::setAttribute(const QString &name, const QVariant &value)
{
    m_impl.m_attribute[name] = value;
}

QVariant IResponse::getAttribute(const QString &name, const QVariant &defaultValue) const
{
    if(m_impl.m_attribute.contains(name)){
        return m_impl.m_attribute[name];
    }
    return defaultValue;
}

$PackageWebCoreEnd
