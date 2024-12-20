﻿#include "IRequest.h"

#include "core/abort/IGlobalAbort.h"
#include "http/mappings/IHttpAction.h"
#include "http/net/impl/IRequestImpl.h"
#include "http/net/ICookieJar.h"
#include "http/net/ISessionJar.h"
#include "http/net/IHeaderJar.h"
#include "http/server/ITcpConnection.h"

$PackageWebCoreBegin

IRequest::IRequest(ITcpConnection& connection)
    : ITcpResolverInterface(connection)
{
    m_impl = new IRequestImpl(*this);
}

IRequest::~IRequest()
{
    delete m_impl;
}

const IString& IRequest::operator[](const IString &header) const
{
    return m_impl->m_headerJar.getRequestHeaderValue(header);
}

const IString& IRequest::operator[](const QString &header) const
{
    return m_impl->m_headerJar.getRequestHeaderValue(header.toUtf8());
}

const ICookieJar& IRequest::cookieJar() const
{
    return m_impl->m_cookieJar;
}

const ISessionJar& IRequest::sessionJar() const
{
    if(!m_impl->m_sessionJar){
        qFatal("error, session not configured");
    }
    return *m_impl->m_sessionJar;
}

const IHeaderJar& IRequest::headerJar() const
{
    return m_impl->m_headerJar;
}

const IMultiPartJar& IRequest::multiPartJar() const
{
    return m_impl->m_multiPartJar;
}

IRequestImpl& IRequest::impl() const
{
    return *m_impl;
}

const IString &IRequest::url() const
{
    return m_impl->m_reqRaw.m_url;
}

IHttpVersion IRequest::version() const
{
    return m_impl->m_reqRaw.m_httpVersion;
}

IHttpMime IRequest::mime() const
{
    return m_impl->m_reqRaw.m_mime;
}

IHttpMethod IRequest::method() const
{
    return m_impl->m_reqRaw.m_method;
}

int IRequest::contentLength() const
{
    return m_impl->m_reqRaw.m_contentLength;
}

const IString& IRequest::contentType() const
{
    return m_impl->m_headerJar.getRequestHeaderValue(IHttpHeader::ContentType);
}

const IString& IRequest::content() const
{
    return m_impl->m_reqRaw.m_body;
}

const QMap<IStringView, IStringView> &IRequest::urlParameters() const
{
    return m_impl->m_reqRaw.m_queries;
}

const QMap<IStringView, IStringView> &IRequest::paramParameters() const
{
    return m_impl->m_reqRaw.m_paths;
}

const QMap<IStringView, IStringView> &IRequest::bodyFormParameters() const
{
    return m_impl->m_reqRaw.m_forms;
}

const std::vector<IMultiPart> &IRequest::bodyMultiParts() const
{
    return m_impl->m_reqRaw.m_multiParts;
}

// TODO: check it
IJson IRequest::bodyJson() const
{
    return m_impl->m_reqRaw.m_json;
}

IStringView IRequest::stash(const char *data)
{
    return m_impl->stash(data);
}

IStringView IRequest::stash(QByteArray &&data)
{
    return m_impl->stash(std::move(data));
}

IStringView IRequest::stash(const QByteArray &data)
{
    return m_impl->stash(data);
}

IStringView IRequest::stash(const QString &data)
{
    return m_impl->stash(data);
}

IStringView IRequest::stash(std::string &&data)
{
    return m_impl->stash(std::move(data));
}

IStringView IRequest::stash(const std::string &data)
{
    return m_impl->stash(data);
}

IStringView IRequest::stash(IString &&data)
{
    return m_impl->stash(std::move(data));
}

IStringView IRequest::stash(const IString &data)
{
    return m_impl->stash(data);
}

IStringView IRequest::stash(IStringView data)
{
    return m_impl->stash(data);
}

/*
QJsonValue IRequest::bodyJson(bool &ok) const
{
//    return impl->requestJson(ok);
    return impl->m_raw->m_requestJson;
}

IStringView IRequest::getParameter(const QString &name, bool& ok) const
{
    return impl->getParameter(name, ok);
}

IResult<IStringView> IRequest::getParameter(const QString &name) const
{
    bool ok;
    auto value = impl->getParameter(name, ok);
    return {std::move(value), ok};
}

IStringView IRequest::getMixedParameter(const QString &name, bool& ok) const
{
    // FIXME:
    return {};
//    return impl->getMixedParameter(name, ok);
}

IResult<IStringView> IRequest::getMixedParameter(const QString &name) const
{
    // FIXME:
    return {IStringView(), false};
    //    bool ok;
//    auto value = impl->getMixedParameter(name, ok);
//    return {std::move(value), ok};
}

IStringView IRequest::getUrlParameter(const QString &name, bool& ok) const
{
    return impl->getUrlParameter(name, ok);
}

IResult<IStringView> IRequest::getUrlParameter(const QString &name) const
{
    bool ok;
    auto value = impl->getUrlParameter(name, ok);
    return {std::move(value), ok};
}

IStringView IRequest::getParamParameter(const QString &name, bool& ok) const
{
    return impl->getParamParameter(name, ok);
}

IResult<IStringView> IRequest::getParamParameter(const QString &name) const
{
    bool ok;
    auto value = impl->getParamParameter(name, ok);
    return {std::move(value), ok};
}

IStringView IRequest::getHeaderParameter(const QString &name, bool& ok) const
{
    return impl->getHeaderParameter(name, ok);
}

IResult<IStringView> IRequest::getHeaderParameter(const QString &name) const
{
    bool ok;
    auto value = impl->getHeaderParameter(name, ok);
    return {std::move(value), ok};
}

IStringView IRequest::getBodyParameter(const QString &name, bool& ok) const
{
    return impl->getBodyParameter(name, ok);
}

IResult<IStringView> IRequest::getBodyParameter(const QString &name) const
{
    bool ok;
    auto value = impl->getBodyParameter(name, ok);
    return {std::move(value), ok};
}

IStringView IRequest::getCookieParameter(const QString &name, bool& ok) const
{
    return impl->getCookieParameter(name, ok);
}

IResult<IStringView> IRequest::getCookieParameter(const QString &name) const
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
*/

//const QMap<QString, QVariant> &IRequest::attributes() const
//{
//    return m_impl->m_attribute;
//}

//bool IRequest::hasAttribute(const QString &name) const
//{
//    return m_impl->m_attribute.contains(name);
//}

//void IRequest::setAttribute(const QString &name, const QVariant &value)
//{
//    m_impl->m_attribute[name] = value;
//}

//QVariant IRequest::getAttribute(const QString &name, bool& ok) const
//{
//    if(m_impl->m_attribute.contains(name)){
//        ok = true;
//        return m_impl->m_attribute[name];
//    }
//    ok = false;
//    return {};
//}

//IResult<QVariant> IRequest::getAttribute(const QString &name) const
//{
//    bool ok;
//    auto value = getAttribute(name, ok);
//    if(ok){
//        return value;
//    }
//    return std::nullopt;
//}

bool IRequest::isValid() const
{
    return m_impl->m_isValid;
}

void IRequest::setInvalidIf(bool condition, IHttpInvalidWare ware) const
{
    if(condition){
        setInvalid(ware);
    }
}

void IRequest::setInvalid(IHttpInvalidWare ware) const
{
    m_impl->setInvalid(ware);
}

//void IRequest::doAction(IHttpAction *action)
//{
//    // TODO: 这里 action 有可能需要被释放，这里需要异步，不能在一个函数里面释放当前的对象
//    action->invoke(*this);
//}

void IRequest::doWrite()
{
    // TODO: 这里也需要异步处理
    m_connection.doWrite();
}

void IRequest::resolve()
{
    m_impl->parseData();
}

std::vector<asio::const_buffer> IRequest::getOutput()
{
    return m_impl->m_respRaw.getContent(*(this->m_impl));
}

$PackageWebCoreEnd
