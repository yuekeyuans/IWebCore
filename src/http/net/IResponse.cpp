#include "IResponse.h"

#include "core/base/IConstantUtil.h"
#include "core/assert/IGlobalAssert.h"
#include "core/assert/IGlobalAbort.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/IHttpAssert.h"
#include "http/net/IRequest.h"
#include "http/net/impl/IRequestRaw.h"
//#include "http/net/impl/IResponseImpl.h"
#include "http/jar/IHeaderJar.h"
#include "http/response/IResponseWare.h"

$PackageWebCoreBegin

$UseAssert(IHttpAssert)

$UseGlobalAssert()

IResponse::IResponse()
{
    IGlobalAbort::abortUnVisibleMethod();
}

IResponse::IResponse(IRequest *request) : m_raw(request->getRaw())
{
    m_raw->m_response = this;
}

IResponse::~IResponse()
{
}

IResponse::IResponse(const IResponse &)
{
    IGlobalAbort::abortUnVisibleMethod();
}

IResponse &IResponse::operator=(const IResponse &)
{
    IGlobalAbort::abortUnVisibleMethod();
    return *this;
}

IResponse::IResponse(IResponse &&)
{
    IGlobalAbort::abortUnVisibleMethod();
}

IResponse &IResponse::operator=(IResponse &&)
{
    IGlobalAbort::abortUnVisibleMethod();
    return *this;
}

IResponse &IResponse::operator<<(const QString &content)
{
    m_raw->m_responseRaw->content.append(content);
    return *this;
}

IResponse &IResponse::operator<<(const QByteArray &content)
{
    m_raw->m_responseRaw->content.append(content);
    return *this;
}

IResponse &IResponse::operator<<(const char *content)
{
    m_raw->m_responseRaw->content.append(QByteArray(content));
    return *this;
}

IResponseHeader IResponse::operator[](const QString &header) const
{
    return {m_raw->m_responseRaw, header};
}

IRequest *IResponse::request() const
{
    return m_raw->m_request;
}

IRequestRaw *IResponse::getRaw() const
{
    return m_raw;
}

IResponse &IResponse::setHeader(const QString &key, const QString &value)
{
    if(key.isEmpty() || value.isEmpty()){
        $Ast->warn("iresponse_setHeader_with_empty_value_or_key");
    }

    m_raw->m_headerJar->setResponseHeader(key, value);
    return *this;
}

IResponse &IResponse::setStatus(IHttpStatusCode statusCode)
{
    m_raw->m_responseRaw->status = statusCode;
    return *this;
}

IResponse &IResponse::setStatus(int statusCode)
{
    m_raw->m_responseRaw->status = IHttpStatus::toStatus(statusCode);
    return *this;
}

IResponse &IResponse::setMime(IHttpMime mime)
{
    m_raw->m_responseRaw->mime = IHttpMimeUtil::toString(mime);
    return *this;
}

IResponse &IResponse::setMime(const QString mime)
{
    m_raw->m_responseRaw->mime = mime;
    return *this;
}

IResponse &IResponse::addCookie(ICookiePart cookiePart)
{
    m_raw->m_responseRaw->cookies.push_back(std::move(cookiePart));
    return *this;
}

IResponse &IResponse::appendContent(const QString &content)
{
    m_raw->m_responseRaw->content.append(content);
    return *this;
}

IResponse &IResponse::appendContent(const QByteArray &content)
{
    m_raw->m_responseRaw->content.append(content);
    return *this;
}

IResponse &IResponse::appendContent(const char *content)
{
    m_raw->m_responseRaw->content.append(content);
    return *this;
}

IResponse &IResponse::setContent(const QString &content)
{
    m_raw->m_responseRaw->content.setContent(content);
    return *this;
}

IResponse &IResponse::setContent(const QByteArray &content)
{
    m_raw->m_responseRaw->content.setContent(content);
    return *this;
}

IResponse &IResponse::setContent(QByteArray &&content)
{
    m_raw->m_responseRaw->content.setContent(std::forward<QByteArray&&>(content));
    return *this;
}

IResponse &IResponse::setContent(const char *content)
{
    m_raw->m_responseRaw->content.setContent(content);
    return *this;
}

IResponse& IResponse::setContent(IResponseWare *response)
{
    if(!m_raw->m_responseRaw->cookies.empty()){
        for(auto val : m_raw->m_responseRaw->cookies){
            response->m_raw->cookies.push_back(val);    // TODO: see whether other effecient way.
        }
    }

    if(!m_raw->m_response->headers().empty()){
        for(const auto& header : m_raw->m_responseRaw->headers){
            if(!response->m_raw->headers.contains(header)){
                const auto& values = m_raw->m_response->headers().values(header);
                for(auto value : values){
                    response->m_raw->headers.insertMulti(header, value);
                }
            }
        }
    }

    std::swap(m_raw->m_responseRaw, response->m_raw);
    return *this;
}

IResponse &IResponse::setContent(IResponseWare &response)
{
    return setContent(&response);
}

IResponse &IResponse::setContent(IHttpInvalidUnit unit)
{
    m_raw->setInvalid(unit);
    return *this;
}

IHttpVersion IResponse::version() const
{
    return m_raw->m_httpVersion;
}

QString IResponse::mime() const
{
    return m_raw->m_responseRaw->mime;
}

IHttpStatusCode IResponse::status() const
{
    return m_raw->m_responseRaw->status;
}

const QMultiHash<QString, QString>& IResponse::headers() const
{
    return m_raw->m_responseRaw->headers;
}

const QMap<QString, QVariant> &IResponse::attributes() const
{
    return m_raw->m_attribute;
}

bool IResponse::hasAttribute(const QString &name) const
{
    return m_raw->m_attribute.contains(name);
}

void IResponse::setAttribute(const QString &name, const QVariant &value)
{
    m_raw->m_attribute[name] = value;
}

QVariant IResponse::getAttribute(const QString &name, const QVariant &defaultValue) const
{
    if(m_raw->m_attribute.contains(name)){
        return m_raw->m_attribute[name];
    }
    return defaultValue;
}

$PackageWebCoreEnd
