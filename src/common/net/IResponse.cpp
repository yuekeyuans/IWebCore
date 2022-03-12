#include "IResponse.h"

#include "assertion/IAssertPreProcessor.h"
#include "base/IConstantUtil.h"

#include "biscuits/IHttpHeader.h"
#include "common/net/IRequest.h"
#include "common/net/impl/IReqRespRaw.h"
#include "common/net/impl/IResponseImpl.h"
#include "common/response/IResponseWare.h"

$PackageWebCoreBegin

IResponse::IResponse()
{
    qFatal("this construct should not be called anywhere");
}

IResponse::IResponse(IRequest *request)
{
    this->raw = request->getRaw();
    raw->m_response = this;
    impl = new IResponseImpl(raw);
}

IResponse &IResponse::operator<<(const QString &content)
{
    raw->m_responseContent.append(content.toUtf8());
    return *this;
}

IResponse &IResponse::operator<<(const QByteArray &content)
{
    raw->m_responseContent.append(content);
    return *this;
}

IResponse &IResponse::operator<<(const char *content)
{
    raw->m_responseContent.append(QByteArray(content));
    return *this;
}

IResponse &IResponse::operator<<(IResponseWare *response)
{
    setContent(response);
    return *this;
}

IResponse &IResponse::operator<<(IResponseWare &response)
{
    setContent(&response);
    return *this;
}

const QString IResponse::operator[](const QString &header) const
{
    if(raw->m_responseHeaders.contains(header)){
        return raw->m_responseHeaders[header];
    }
    return "";
}

QString &IResponse::operator[](const QString &header)
{
    return raw->m_responseHeaders[header];
}

IRequest *IResponse::request() const
{
    return raw->m_request;
}

IReqRespRaw *IResponse::getRaw() const
{
    return raw;
}

IResponse &IResponse::setHeader(const QString &key, const QString &value)
{
    if(key.isEmpty() || value.isEmpty()){
        $AssertWarning(iresponse_setHeader_with_empty_value_or_key)
    }

    raw->m_responseHeaders[key] = value;
    return *this;
}

IResponse &IResponse::setStatus(IHttpStatus statusCode)
{
    raw->m_responseStatus = statusCode;
    return *this;
}

IResponse &IResponse::setMime(IHttpMime mime)
{
    raw->m_responseMime = mime;
    return *this;
}

IResponse &IResponse::addCookie(const ICookiePart &cookiePart)
{
    raw->m_responseCookies.append(cookiePart);
    return *this;
}

IResponse &IResponse::appendContent(const QString &content)
{
    raw->m_responseContent.append(content);
    return *this;
}

IResponse &IResponse::appendContent(const QByteArray &content)
{
    raw->m_responseContent.append(content);
    return *this;
}

IResponse &IResponse::appendContent(const char *content)
{
    raw->m_responseContent.append(content);
    return *this;
}

IResponse &IResponse::setContent(const QString &content)
{
    raw->m_responseContent = content.toUtf8();
    return *this;
}

IResponse &IResponse::setContent(const QByteArray &content)
{
    raw->m_responseContent = content;
    return *this;
}

IResponse &IResponse::setContent(QByteArray &&content)
{
    std::swap(raw->m_responseContent, content);
    return *this;
}

IResponse &IResponse::setContent(const char *content)
{
    raw->m_responseContent = QByteArray(content);
    return *this;
}

IResponse& IResponse::setContent(IResponseWare *response)
{
    std::swap(raw->m_responseContent, response->content());

    if(raw->m_responseStatus == IHttpStatus::UNKNOWN){
        raw->m_responseStatus = response->status();
    }

    if(raw->m_responseMime == IHttpMime::UNKNOWN){
        raw->m_responseMime = response->mime();
    }

    auto& headers = response->headers();
    auto keys = headers.keys();
    for(auto key : keys){
        if(!raw->m_responseHeaders.contains(key)){
            raw->m_responseHeaders[key] = headers[key];
        }
    }

    if((!raw->m_responseHeaders.contains(IHttpHeader::ContentType)
         || raw->m_responseHeaders[IHttpHeader::ContentType] == "UNKNOWN")
        && raw->m_responseMime != IHttpMime::UNKNOWN){
        raw->m_responseHeaders[IHttpHeader::ContentType] = IHttpMimeHelper::toString(raw->m_responseMime);
    }
    return *this;
}

IHttpVersion IResponse::version() const
{
    return raw->m_httpVersion;
}

IHttpMime IResponse::mime() const
{
    return raw->m_responseMime;
}

IHttpStatus IResponse::status() const
{
    return raw->m_responseStatus;
}

const QMap<QString, QString>& IResponse::headers() const
{
    return raw->m_responseHeaders;
}

const QByteArray &IResponse::content() const
{
    return raw->m_responseContent;
}

const QMap<QString, QVariant> &IResponse::attributes() const
{
    return raw->m_attribute;
}

bool IResponse::hasAttribute(const QString &name) const
{
    return raw->m_attribute.contains(name);
}

void IResponse::setAttribute(const QString &name, const QVariant &value)
{
    raw->m_attribute[name] = value;
}

QVariant IResponse::getAttribute(const QString &name, const QVariant &defaultValue) const
{
    if(raw->m_attribute.contains(name)){
        return raw->m_attribute[name];
    }
    return defaultValue;
}

bool IResponse::respond()
{
    return impl->respond();
}

bool IResponse::valid() const
{
    return raw->m_valid;
}

void IResponse::setInvalidIf(bool condition, IHttpStatus status, const QString &message) const
{
    raw->setInvalidIf(condition, status, message);
}

void IResponse::setInvalid(IHttpStatus status, const QString &message) const
{
    raw->setInvalid(status, message);
}

$PackageWebCoreEnd
