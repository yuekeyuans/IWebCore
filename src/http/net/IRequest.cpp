#include "IRequest.h"

#include "core/base/IConvertUtil.h"
#include "core/base/IConstantUtil.h"
#include "core/base/IJsonUtil.h"
#include "core/base/IXmlUtil.h"
#include "core/base/IToeUtil.h"
#include "core/assert/IGlobalAssert.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/IHttpAssert.h"
#include "http/invalid/IHttpRequestTimeoutInvalid.h"
#include "http/net/impl/IRequestImpl.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/jar/ICookieJar.h"
#include "http/jar/ISessionJar.h"
#include "http/jar/IHeaderJar.h"
#include "http/server/IHttpServerManage.h"

$PackageWebCoreBegin

$UseAssert(IHttpAssert)
$UseGlobalAssert()

IRequest::IRequest() : ITcpResolverInterface(nullptr)
{
    qFatal(IConstantUtil::UnVisibleMethod);
}

IRequest::IRequest(ITcpConnection *connection) : ITcpResolverInterface(connection)
{
    impl = new IRequestImpl(this);
}

IRequest::~IRequest()
{
    delete impl;
}

IRequest::IRequest(const IRequest &) : ITcpResolverInterface(nullptr)
{
    qFatal(IConstantUtil::UnVisibleMethod);
}

IRequest &IRequest::operator=(const IRequest &)
{
    qFatal(IConstantUtil::UnVisibleMethod);
    return *this;
}

IRequest::IRequest(IRequest &&) : ITcpResolverInterface(nullptr)
{
    qFatal(IConstantUtil::UnVisibleMethod);
}

IRequest &IRequest::operator=(IRequest &&)
{
    qFatal(IConstantUtil::UnVisibleMethod);
    return *this;
}

// TODO: 这个考虑返回 IResult
// TODO: 这个返回不应该是 IResult, 而应该是 引用类型
const QString IRequest::operator[](const QString &header) const
{
    bool ok;
    return impl->m_raw->m_headerJar->getRequestHeaderValue(header, ok);
}

IResponse *IRequest::response() const
{
    return impl->m_raw->m_response;
}

ICookieJar *IRequest::cookieJar() const
{
    return impl->m_raw->m_cookieJar;
}

ISessionJar *IRequest::sessionJar() const
{
    return impl->m_raw->m_sessionJar;
}

IHeaderJar *IRequest::headerJar() const
{
    return impl->m_raw->m_headerJar;
}

IMultiPartJar *IRequest::multiPartJar() const
{
    return impl->m_raw->m_multiPartJar;
}

IRequestRaw *IRequest::getRaw() const
{
    return impl->m_raw;
}

IHttpVersion IRequest::version() const
{
    return impl->m_raw->m_httpVersion;
}

IHttpMime IRequest::mime() const
{
    return impl->m_raw->m_requestMime;
}

const QString &IRequest::url() const
{
    return impl->m_raw->m_url;
}

IHttpMethod IRequest::method() const
{
    return impl->m_raw->m_method;
}

int IRequest::bodyContentLength() const
{
    return impl->contentLength();
}

QString IRequest::bodyContentType() const
{
    return impl->contentType();
}

const QByteArray &IRequest::bodyContent() const
{
    return impl->m_raw->m_requestBody;
}

QMultiHash<QString, QString> &IRequest::headers()
{
    return impl->m_raw->m_requestHeaders;
}

const QMultiHash<QString, QString> &IRequest::headers() const
{
    return impl->m_raw->m_requestHeaders;
}

const QMap<QString, QString> &IRequest::urlParameters() const
{
    return impl->m_raw->m_requestUrlParameters;
}

const QMap<QString, QString> &IRequest::paramParameters() const
{
    return impl->m_raw->m_requestPathParameters;
}

const QMap<QString, QString> &IRequest::bodyFormParameters() const
{
    return impl->m_raw->m_requestBodyParameters;
}

const QVector<IMultiPart> &IRequest::bodyMultiParts() const
{
    return impl->m_raw->m_requestMultiParts;
}

QJsonValue IRequest::bodyJson(bool &ok) const
{
    return impl->requestJson(ok);
}

QByteArray IRequest::getParameter(const QString &name, bool& ok) const
{
    return impl->getParameter(name, ok);
}

IResult<QByteArray> IRequest::getParameter(const QString &name) const
{
    bool ok;
    auto value = impl->getParameter(name, ok);
    return {std::move(value), ok};
}

QByteArray IRequest::getMixedParameter(const QString &name, bool& ok) const
{
    return impl->getMixedParameter(name, ok);
}

IResult<QByteArray> IRequest::getMixedParameter(const QString &name) const
{
    bool ok;
    auto value = impl->getMixedParameter(name, ok);
    return {std::move(value), ok};
}

QByteArray IRequest::getUrlParameter(const QString &name, bool& ok) const
{
    return impl->getUrlParameter(name, ok);
}

IResult<QByteArray> IRequest::getUrlParameter(const QString &name) const
{
    bool ok;
    auto value = impl->getUrlParameter(name, ok);
    return {std::move(value), ok};
}

QByteArray IRequest::getParamParameter(const QString &name, bool& ok) const
{
    return impl->getParamParameter(name, ok);
}

IResult<QByteArray> IRequest::getParamParameter(const QString &name) const
{
    bool ok;
    auto value = impl->getParamParameter(name, ok);
    return {std::move(value), ok};
}

QByteArray IRequest::getHeaderParameter(const QString &name, bool& ok) const
{
    return impl->getHeaderParameter(name, ok);
}

IResult<QByteArray> IRequest::getHeaderParameter(const QString &name) const
{
    bool ok;
    auto value = impl->getHeaderParameter(name, ok);
    return {std::move(value), ok};
}

QByteArray IRequest::getBodyParameter(const QString &name, bool& ok) const
{
    return impl->getBodyParameter(name, ok);
}

IResult<QByteArray> IRequest::getBodyParameter(const QString &name) const
{
    bool ok;
    auto value = impl->getBodyParameter(name, ok);
    return {std::move(value), ok};
}

QByteArray IRequest::getCookieParameter(const QString &name, bool& ok) const
{
    return impl->getCookieParameter(name, ok);
}

IResult<QByteArray> IRequest::getCookieParameter(const QString &name) const
{
    bool ok;
    auto value = impl->getCookieParameter(name, ok);
    return {std::move(value), ok};
}

QByteArray IRequest::getSessionParameter(const QString &name, bool& ok) const
{
    return impl->getSessionParameter(name, ok);
}

IResult<QByteArray> IRequest::getSessionParameter(const QString &name) const
{
    bool ok;
    auto value = impl->getSessionParameter(name, ok);
    return {std::move(value), ok};
}

const QMap<QString, QVariant> &IRequest::attributes() const
{
    return impl->m_raw->m_attribute;
}

bool IRequest::hasAttribute(const QString &name) const
{
    return impl->m_raw->m_attribute.contains(name);
}

void IRequest::setAttribute(const QString &name, const QVariant &value)
{
    impl->m_raw->m_attribute[name] = value;
}

QVariant IRequest::getAttribute(const QString &name, bool& ok) const
{
    if(impl->m_raw->m_attribute.contains(name)){
        ok = true;
        return impl->m_raw->m_attribute[name];
    }
    ok = false;
    return {};
}

IResult<QVariant> IRequest::getAttribute(const QString &name) const
{
    bool ok;
    auto value = getAttribute(name, ok);
    return {value, ok};
}

bool IRequest::valid() const
{
    return impl->m_raw->valid();
}

void IRequest::setInvalidIf(bool condition, IHttpInvalidUnit ware) const
{
    if(condition){
        impl->m_raw->setInvalid(ware);
    }
}

void IRequest::setInvalid(IHttpInvalidUnit ware) const
{
    return impl->m_raw->setInvalid(ware);
}

void IRequest::resolve()
{
    impl->parseData();
}

std::vector<asio::const_buffer> IRequest::getResult()
{
    return impl->getResult();
}

$PackageWebCoreEnd
