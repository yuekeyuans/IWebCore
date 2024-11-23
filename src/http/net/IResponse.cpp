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

IResponse::~IResponse()
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

// TODO: warn
IResponse &IResponse::setHeader(const QString &key, const QString &value)
{
    if(key.isEmpty() || value.isEmpty()){
//        $Ast->warn("iresponse_setHeader_with_empty_value_or_key");
    }

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
    m_impl.m_respRaw.setContent(std::forward<QByteArray&&>(content));
    return *this;
}

IResponse &IResponse::setContent(const char *content)
{
    m_impl.m_respRaw.setContent(content);
    return *this;
}

IResponse& IResponse::setContent(IResponseWare *response)
{
    if(!response->mime().isEmpty()){
        m_impl.m_respRaw.m_mime = response->mime();
    }
    if(response->status() != m_impl.m_respRaw.m_status){
        m_impl.m_respRaw.m_status = response->status();
    }

    // TODO: 先不做, 这个还是有一点复杂， 因为可能涉及到多值的情况
    if(!response->headers().isEmpty()){
        auto keys = response->headers().keys();
        for(const auto& key : keys){
            this->setHeader(key, response->headers().value(key));
//            m_impl.m_respRaw.m_headers
        }
    }
    while(!response->m_raw->m_contents.empty()){
        m_impl.m_respRaw.m_contents.push_back(response->m_raw->m_contents.front());
        response->m_raw->m_contents.pop_front();
    }
    return *this;
}

IResponse &IResponse::setContent(IResponseWare &response)
{
    return setContent(&response);
}

IResponse &IResponse::setContent(IHttpInvalidWare unit)
{
    m_impl.m_request.setInvalid(unit);
    return *this;
}

IHttpVersion IResponse::version() const
{
    return m_impl.m_reqRaw.m_httpVersion;
}

const QString& IResponse::mime() const
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
