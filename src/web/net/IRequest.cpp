#include "IRequest.h"

#include "core/base/IConvertUtil.h"
#include "core/base/IConstantUtil.h"
#include "core/base/IJsonUtil.h"
#include "core/base/IXmlUtil.h"
#include "core/base/IToeUtil.h"
#include "core/base/ISocketUtil.h"
#include "core/assert/IGlobalAssert.h"
#include "web/IWebAssert.h"
#include "web/biscuits/IHttpHeader.h"
#include "web/net/impl/IRequestImpl.h"
#include "web/net/impl/IReqRespRaw.h"
#include "web/jar/ICookieJar.h"
#include "web/jar/ISessionJar.h"
#include "web/jar/IHeaderJar.h"
#include "web/server/IHttpServerManage.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)
$UseGlobalAssert()

IRequest::IRequest()
{
    $Ast->fatal("IRequest_IResponse_CREATE_ERROR");
}

IRequest::IRequest(qintptr handle)
    : IRequest(ISocketUtil::createTcpSocket(handle))
{
}

IRequest::IRequest(QTcpSocket *socket)
{
    raw = new IReqRespRaw(this, socket);
    impl = new IRequestImpl(raw);

    // TODO: 这里如果只是连接上了，但是没有通信的话，它会卡住线程，如果多余 idealThreadCount 的话，软件就会明显卡顿起来。
    // 所以这里考虑 将数据处理和数据接收分离开来， 
    // 数据接收 -> 满足条件 -> 数据处理
    //        |-> 不满足条件 -> 压栈等待
    //        |-> 失联或超时 -> invalid, 并且关闭线程。
    // 目的就是把软件的时间给省出来。
    if(!raw->waitSocketForReadyRead()){
        setInvalid(IHttpStatus::REQUEST_TIMEOUT_408, "request open failed");
    }else{
        impl->resolve();
    }
}

IRequest::~IRequest()
{
//    bool ok;
//    auto connection = getHeaderParameter("Connection", &ok);
//    if(ok && connection.contains("keep-alive")){
//        qDebug() << connection;
//        IHttpServerManage::addSocket(raw->m_socket);
//    }else{
        ISocketUtil::closeTcpSocket(raw->m_socket);
        delete raw->m_socket;
//    }

    delete raw;
    delete impl;
}

IRequest::IRequest(const IRequest &)
{
    $Ast->fatal("IRequest_IResponse_COPY_MOVE_ERROR");
}

IRequest &IRequest::operator=(const IRequest &)
{
    $Ast->fatal("IRequest_IResponse_COPY_MOVE_ERROR");
    return *this;
}

IRequest::IRequest(IRequest &&)
{
    $Ast->fatal("IRequest_IResponse_COPY_MOVE_ERROR");
}

IRequest &IRequest::operator=(IRequest &&)
{
    $Ast->fatal("IRequest_IResponse_COPY_MOVE_ERROR");
    return *this;
}

// TODO: 这个考虑返回 IResult
// TODO: 这个返回不应该是 IResult, 而应该是 引用类型
const QString IRequest::operator[](const QString &header) const
{
    bool ok;
    return raw->m_headerJar->getRequestHeaderValue(header, ok);
}

IResponse *IRequest::response() const
{
    return raw->m_response;
}

ICookieJar *IRequest::cookieJar() const
{
    return raw->m_cookieJar;
}

ISessionJar *IRequest::sessionJar() const
{
    return raw->m_sessionJar;
}

IHeaderJar *IRequest::headerJar() const
{
    return raw->m_headerJar;
}

IMultiPartJar *IRequest::multiPartJar() const
{
    return raw->m_multiPartJar;
}

IReqRespRaw *IRequest::getRaw() const
{
    return raw;
}

IHttpVersion IRequest::version() const
{
    return raw->m_httpVersion;
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

QList<QPair<QString, QString> > &IRequest::headers()
{
    return raw->m_requestHeaders;
}

const QList<QPair<QString, QString>> &IRequest::headers() const
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

QJsonValue IRequest::bodyJson(bool &ok) const
{
    return impl->requestJson(ok);
}

//const QDomNode &IRequest::bodyXml(bool& ok) const
//{
//    return impl->requestXml(ok);
//}

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

QByteArray IRequest::getAppParameter(const QString &name, bool& ok) const
{
    return impl->getAppParameter(name, ok);
}

IResult<QByteArray> IRequest::getAppParameter(const QString &name) const
{
    bool ok;
    auto value = impl->getAppParameter(name, ok);
    return {std::move(value), ok};
}

QByteArray IRequest::getSystemParameter(const QString &name, bool& ok) const
{
    return impl->getSystemParameter(name, ok);
}

IResult<QByteArray> IRequest::getSystemParameter(const QString &name) const
{
    bool ok;
    auto value = impl->getSystemParameter(name, ok);
    return {std::move(value), ok};
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

QVariant IRequest::getAttribute(const QString &name, bool& ok) const
{
    if(raw->m_attribute.contains(name)){
        ok = true;
        return raw->m_attribute[name];
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
