#include "IRequest.h"
#include "base/IConstantUtil.h"
#include "base/IConvertUtil.h"
#include "base/IJsonUtil.h"
#include "base/IXmlUtil.h"
#include "biscuits/IHttpHeader.h"
#include "common/net/impl/IRequestImpl.h"
#include "common/net/impl/IReqRespRaw.h"
#include "common/cookie/ICookieJar.h"
#include "common/session/ISessionJar.h"

$PackageWebCoreBegin

IRequest::IRequest()
{
    raw = new IReqRespRaw;
    raw->m_request = this;
    impl = new IRequestImpl(raw);
}

IRequest::IRequest(QTcpSocket *socket)
{
    raw = new IReqRespRaw;
    raw->m_request = this;
    raw->m_socket = socket;
    impl = new IRequestImpl(raw);
    impl->resolve();
}

IRequest::~IRequest()
{
    if(raw != nullptr){
        delete raw;
        raw = nullptr;
    }
}

// TODO: 这个需要修改
const QString IRequest::operator[](const QString &header) const
{
    return raw->m_headerJar.getRequestHeaderValue(header, nullptr);
}

IResponse *IRequest::response() const
{
    return raw->m_response;
}

ICookieJar *IRequest::cookieJar() const
{
    return &raw->m_cookieJar;
}

ISessionJar *IRequest::sessionJar() const
{
    qFatal(IConstantUtil::UnImplimentedMethod);
    return &raw->m_sessionJar;
}

IHeaderJar *IRequest::headerJar() const
{
    return &raw->m_headerJar;
}

IReqRespRaw *IRequest::getRaw() const
{
    return raw;
}

IHttpVersion IRequest::version() const
{
    return raw->m_httpVersion;
}

IHttpCharset IRequest::charset() const
{
    qFatal(IConstantUtil::UnImplimentedMethod);
    return IHttpCharset::UTF_8;
}

IHttpMime IRequest::mime() const
{
    return raw->m_requestMime;
}

const QString &IRequest::url() const
{
    return raw->m_url;
}

IHttpMethod IRequest::method() const
{
    return raw->m_method;
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
    return raw->m_requestBody;
}

QList<QPair<QString, QByteArray> > &IRequest::headers()
{
    return raw->m_requestHeaders;
}

const QList<QPair<QString, QByteArray>> &IRequest::headers() const
{
    return raw->m_requestHeaders;
}

const QMap<QString, QByteArray> &IRequest::urlParameters() const
{
    return raw->m_requestUrlParameters;
}

const QMap<QString, QByteArray> &IRequest::paramParameters() const
{
    return raw->m_requestParamParameters;
}

const QMap<QString, QByteArray> &IRequest::bodyFormParameters() const
{
    return raw->m_requestBodyParameters;
}

const QVector<IMultiPart> &IRequest::bodyMultiParts() const
{
    return raw->m_requestMultiParts;
}

const QJsonValue &IRequest::bodyJson(bool* ok) const
{
    return impl->requestJson(ok);
}

const QDomNode &IRequest::bodyXml(bool* ok) const
{
    return impl->requestXml(ok);
}

QByteArray IRequest::getParameter(const QString &name, bool*ok) const
{
    return impl->getParameter(name, ok);
}

QByteArray IRequest::getMixedParameter(const QString &name, bool *ok) const
{
    return impl->getMixedParameter(name, ok);
}

QByteArray IRequest::getUrlParameter(const QString &name, bool* ok) const
{
    return impl->getUrlParameter(name, ok);
}

QByteArray IRequest::getParamParameter(const QString &name, bool* ok) const
{
    return impl->getParamParameter(name, ok);
}

QByteArray IRequest::getHeaderParameter(const QString &name, bool* ok) const
{
    return impl->getHeaderParameter(name, ok);
}

QByteArray IRequest::getBodyParameter(const QString &name, bool* ok) const
{
    return impl->getBodyParameter(name, ok);
}

QByteArray IRequest::getCookieParameter(const QString &name, bool* ok) const
{
    return impl->getCookieParameter(name, ok);
}

QByteArray IRequest::getSessionParameter(const QString &name, bool* ok) const
{
    return impl->getSessionParameter(name, ok);
}

QByteArray IRequest::getAppParameter(const QString &name, bool* ok) const
{
    return impl->getAppParameter(name, ok);
}

QByteArray IRequest::getSystemParameter(const QString &name, bool* ok) const
{
    return impl->getSystemParameter(name, ok);
}

const QMap<QString, QVariant> &IRequest::attributes() const
{
    return raw->m_attribute;
}

bool IRequest::hasAttribute(const QString &name) const
{
    return raw->m_attribute.contains(name);
}

void IRequest::setAttribute(const QString &name, const QVariant &value)
{
    raw->m_attribute[name] = value;
}

QVariant IRequest::getAttribute(const QString &name, bool* ok) const
{
    IToeUtil::setOk(ok, true);
    if(raw->m_attribute.contains(name)){
        return raw->m_attribute[name];
    }
    IToeUtil::setOk(ok, false);
    return {};
}

bool IRequest::valid() const
{
    return raw->m_valid;
}

void IRequest::setInvalidIf(bool condition, IHttpStatus status, const QString &message) const
{
    return raw->setInvalidIf(condition, status, message);
}

void IRequest::setInvalid(IHttpStatus status, const QString &message) const
{
    return raw->setInvalid(status, message);
}

$PackageWebCoreEnd
