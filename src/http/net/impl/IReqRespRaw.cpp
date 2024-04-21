#include "IReqRespRaw.h"
#include "core/base/IHeaderUtil.h"
#include "core/base/IConstantUtil.h"
#include "core/base/IToeUtil.h"
#include "core/base/IJsonUtil.h"
#include "core/base/IXmlUtil.h"

#include "http/jar/ICookieJar.h"
#include "http/jar/IHeaderJar.h"
#include "http/jar/ISessionJar.h"
#include "http/jar/IMultiPartJar.h"
#include "http/IWebAssert.h"

#include "http/session/ISessionManager.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

IReqRespRaw::IReqRespRaw()
{
    $Ast->fatal("IReqResp_CREATE_ERROR");
}

IReqRespRaw::IReqRespRaw(IRequest *request, QTcpSocket *socket)
{
    m_request = request;
    m_socket = socket;

    m_headerJar = new IHeaderJar(this);
    m_cookieJar = new ICookieJar(this);
    m_multiPartJar = new IMultiPartJar(this);

    if(ISessionManager::instance()->getSessionWare() != nullptr){
        m_sessionJar = new ISessionJar(this);
    }
}

IReqRespRaw::~IReqRespRaw()
{
    delete m_headerJar;
    delete m_cookieJar;
    delete m_multiPartJar;
    delete m_sessionJar;
}

bool IReqRespRaw::valid() const
{
    return this->m_valid;
}

void IReqRespRaw::setInvalid(IHttpStatus status, const QString &message)
{
    this->m_valid = false;
    this->m_responseMime = IHttpMimeHelper::toString(IHttpMime::TEXT_PLAIN_UTF8);
    this->m_responseStatus = status;

    QString tip = IHttpStatusHelper::toString(status).append(" - ")
                      .append(IHttpStatusHelper::toStringDescription(status)).append(": ")
                      .append(message).append(IConstantUtil::NewLine);
    this->m_responseContent.setContent(tip);
}

void IReqRespRaw::setInvalidIf(bool condition, IHttpStatus status, const QString &message)
{
    if(condition){
        setInvalid(status, message);
    }
}

// TODO: 这里需要查看一下，感觉返回数据过于早了，应该统一处理的。
QJsonValue IReqRespRaw::getRequestJson(bool& ok)
{
    if(!isJsonInited){
        m_requestJson = IJsonUtil::toJsonValue(m_requestBody, ok);
        setInvalidIf(!ok, IHttpStatus::BAD_REQUEST_400, "convert body to json failed");
        isJsonInited = true;
    }
    ok = true;
    return m_requestJson;
}

IResult<QJsonValue> IReqRespRaw::getRequestJson()
{
    bool ok;
    auto value = getRequestJson(ok);
    return {value, ok};
}

// TODO: xml 不再被支持， 以后考虑支持
//QDomNode &IReqRespRaw::getRequestXml(bool& ok)
//{
//    IToeUtil::setOk(ok, true);
//    if(!isXmlInited){
//        m_requestXml = IXmlUtil::toXml(m_requestBody, ok);
//        setInvalidIf(!ok, IHttpStatus::BAD_REQUEST_400, "convert body to xml failed");
//        isXmlInited = true;
//    }
//    return m_requestXml;
//}

void IReqRespRaw::writeSocket(const QByteArray &content)
{
    m_socket->write(content);
}

void IReqRespRaw::writeSocket(QByteArray &&content)
{
    m_socket->write(std::forward<QByteArray>(content));
}

void IReqRespRaw::flushSocket()
{
    m_socket->flush();
}

bool IReqRespRaw::waitSocketForReadyRead(int time)
{
    return m_socket->waitForReadyRead(time);
}

QByteArray IReqRespRaw::readSocketLine(qint64 cnt)
{
    return m_socket->readLine(cnt);
}

QByteArray IReqRespRaw::readSocket(qint64 length)
{
    return m_socket->read(length);
}

bool IReqRespRaw::canSocketReadLine()
{
    return m_socket->canReadLine();
}

$PackageWebCoreEnd
