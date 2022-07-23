#include "IResponse.h"

#include "base/IConstantUtil.h"
#include "core/assert/IGlobalAssert.h"
#include "web/biscuits/IHttpHeader.h"
#include "web/net/IRequest.h"
#include "web/net/impl/IReqRespRaw.h"
#include "web/net/impl/IResponseImpl.h"
#include "web/response/IResponseWare.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseGlobalAssert();
$UseAssert(IWebAssert)

IResponse::IResponse()
{
    qFatal(IConstantUtil::UnCallableMethod);
}

IResponse::IResponse(IRequest *request)
{
    this->raw = request->getRaw();
    raw->m_response = this;
    impl = new IResponseImpl(raw);
}

IResponse &IResponse::operator<<(const QString &content)
{
    raw->m_responseContent.append(content);
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

QString IResponse::operator[](const QString &header) const
{
    auto it=raw->m_responseHeaders.begin();
    for(; it!= raw->m_responseHeaders.end(); it++){
        if(it->first == header){
            return it->second;
        }
    }

    return "";
}

QString &IResponse::operator[](const QString &header)
{
    auto it=raw->m_responseHeaders.begin();
    for(; it!= raw->m_responseHeaders.end(); it++){
        if(it->first == header){
            return it->second;
        }
    }
    QPair<QString, QByteArray> pair{header, ""};
    raw->m_responseHeaders.append(pair);
    return raw->m_responseHeaders.last().second;
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
        $Ast->warn("iresponse_setHeader_with_empty_value_or_key");
    }

    raw->m_headerJar.setResponseHeader(key, value);
    return *this;
}

IResponse &IResponse::setStatus(IHttpStatus statusCode)
{
    raw->m_responseStatus = statusCode;
    return *this;
}

// NOTE: 这里是强转， 也就是说，任何一个数据都可以被设置进来。
IResponse &IResponse::setStatus(int statusCode)
{
    raw->m_responseStatus = IHttpStatus(statusCode);
    return *this;
}

IResponse &IResponse::setMime(IHttpMime mime)
{
    raw->m_responseMime = IHttpMimeHelper::toString(mime);
    return *this;
}

IResponse &IResponse::setMime(const QString mime)
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
    raw->m_responseContent.setContent(content);
    return *this;
}

IResponse &IResponse::setContent(const QByteArray &content)
{
    raw->m_responseContent.setContent(content);
    return *this;
}

IResponse &IResponse::setContent(QByteArray &&content)
{
    raw->m_responseContent.setContent(std::forward<QByteArray&&>(content));
    return *this;
}

IResponse &IResponse::setContent(const char *content)
{
    raw->m_responseContent.setContent(content);
    return *this;
}

IResponse& IResponse::setContent(IResponseWare *response)
{
    std::swap(raw->m_responseContent, response->getContent());

    if(raw->m_responseStatus == IHttpStatus::UNKNOWN){
        raw->m_responseStatus = response->status();
    }

    if(raw->m_responseMime == IHttpMimeHelper::MIME_UNKNOWN_STRING){
        raw->m_responseMime = response->mime();
    }

    auto& headers = response->headers();
    auto keys = headers.keys();
    for(auto key : keys){
        if(!raw->m_headerJar.containResponseHeaderKey(key)){
            raw->m_headerJar.addResponseHeader(key, headers[key]);
            // TODO: 这里可能有冲突，需要特殊处理掉
        }
    }

    if((!raw->m_headerJar.containResponseHeaderKey(IHttpHeader::ContentType)
         || raw->m_headerJar.getResponseHeaderValue(IHttpHeader::ContentType, nullptr) == "UNKNOWN")
        && raw->m_responseMime != IHttpMimeHelper::MIME_UNKNOWN_STRING){
        raw->m_headerJar.setResponseHeader(IHttpHeader::ContentType, raw->m_responseMime);
    }
    return *this;
}

IResponse &IResponse::setContent(IResponseWare &response)
{
    return setContent(&response);
}

IHttpVersion IResponse::version() const
{
    return raw->m_httpVersion;
}

QString IResponse::mime() const
{
    return raw->m_responseMime;
}

IHttpStatus IResponse::status() const
{
    return raw->m_responseStatus;
}

const QList<QPair<QString, QString>>& IResponse::headers() const
{
    return raw->m_responseHeaders;
}

//const QByteArray &IResponse::content() const
//{
//    return raw->m_responseContent;
//}

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
