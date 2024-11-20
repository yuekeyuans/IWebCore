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

IResponse &IResponse::operator=(const IResponse &)
{
    IGlobalAbort::abortUnVisibleMethod();
    return *this;
}

IResponse::IResponse(IResponse &&) : m_impl(*static_cast<IRequestImpl*>(nullptr))
{
    IGlobalAbort::abortUnVisibleMethod();
}

IResponse &IResponse::operator=(IResponse &&)
{
    IGlobalAbort::abortUnVisibleMethod();
    return *this;
}

IResponseHeader IResponse::operator[](const QString &header) const
{
    return {&m_impl.m_respRaw, header};
}

// TODO: warn
IResponse &IResponse::setHeader(const QString &key, const QString &value)
{
    if(key.isEmpty() || value.isEmpty()){
//        $Ast->warn("iresponse_setHeader_with_empty_value_or_key");
    }

    m_impl.m_reqRaw.m_headerJar->setResponseHeader(key, value);
    return *this;
}

IResponse &IResponse::setStatus(IHttpStatus statusCode)
{
    m_impl.m_respRaw.status = statusCode;
    return *this;
}

IResponse &IResponse::setStatus(int statusCode)
{
    m_impl.m_respRaw.status = IHttpStatusUtil::toStatus(statusCode);
    return *this;
}

IResponse &IResponse::setMime(IHttpMime mime)
{
    m_impl.m_respRaw.mime = IHttpMimeUtil::toString(mime);
    return *this;
}

IResponse &IResponse::setMime(const QString mime)
{
    m_impl.m_respRaw.mime = mime;
    return *this;
}

IResponse &IResponse::addCookie(ICookiePart cookiePart)
{
    m_impl.m_respRaw.cookies.push_back(std::move(cookiePart));
    return *this;
}

IResponse &IResponse::setContent(const QString &content)
{
    m_impl.m_respRaw.content.setContent(content);
    return *this;
}

IResponse &IResponse::setContent(const QByteArray &content)
{
    m_impl.m_respRaw.content.setContent(content);
    return *this;
}

IResponse &IResponse::setContent(QByteArray &&content)
{
    m_impl.m_respRaw.content.setContent(std::forward<QByteArray&&>(content));
    return *this;
}

IResponse &IResponse::setContent(const char *content)
{
    m_impl.m_respRaw.content.setContent(content);
    return *this;
}

IResponse& IResponse::setContent(IResponseWare *response)
{
    if(!m_impl.m_respRaw.cookies.empty()){
        for(auto val : m_impl.m_respRaw.cookies){
            response->m_raw->cookies.push_back(val);    // TODO: see whether other effecient way.
        }
    }

    if(!headers().empty()){
        for(const auto& header : m_impl.m_respRaw.headers){
            if(!response->m_raw->headers.contains(header)){
                const auto& values = headers().values(header);
                for(auto value : values){
                    response->m_raw->headers.insertMulti(header, value);
                }
            }
        }
    }

    // TODO: 检查一下
    std::swap(m_impl.m_respRaw, *(response->m_raw));
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

QString IResponse::mime() const
{
    return m_impl.m_respRaw.mime;
}

IHttpStatus IResponse::status() const
{
    return m_impl.m_respRaw.status;
}

const QMultiHash<QString, QString>& IResponse::headers() const
{
    return m_impl.m_respRaw.headers;
}

const QMap<QString, QVariant> &IResponse::attributes() const
{
    return m_impl.m_reqRaw.m_attribute;
}

bool IResponse::hasAttribute(const QString &name) const
{
    return m_impl.m_reqRaw.m_attribute.contains(name);
}

void IResponse::setAttribute(const QString &name, const QVariant &value)
{
    m_impl.m_reqRaw.m_attribute[name] = value;
}

QVariant IResponse::getAttribute(const QString &name, const QVariant &defaultValue) const
{
    if(m_impl.m_reqRaw.m_attribute.contains(name)){
        return m_impl.m_reqRaw.m_attribute[name];
    }
    return defaultValue;
}

$PackageWebCoreEnd
