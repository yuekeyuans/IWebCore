#include "IReqRespRaw.h"
#include "base/IHeaderUtil.h"
#include "base/IConstantUtil.h"
#include "base/IToeUtil.h"
#include "base/IJsonUtil.h"
#include "base/IXmlUtil.h"

#include "web/jar/ICookieJar.h"
#include "web/jar/IHeaderJar.h"
#include "web/jar/ISessionJar.h"
#include "web/jar/IMultiPartJar.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

IReqRespRaw::IReqRespRaw()
{
    $Ast->fatal("IReqResp_CREATE_ERROR");
}

IReqRespRaw::IReqRespRaw(IRequest *request, QTcpSocket *socket) : IReqRespRaw()
{
    m_request = request;
    m_socket = socket;

    m_headerJar = new IHeaderJar(this);
    m_cookieJar = new ICookieJar(this);
    m_multiPartJar = new IMultiPartJar(this);
    m_sessionJar = new ISessionJar(this);
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

QJsonValue &IReqRespRaw::getRequestJson(bool *ok)
{
    IToeUtil::setOk(ok, true);
    bool convertOk;
    if(!isJsonInited){
        m_requestJson = IJsonUtil::toJsonValue(m_requestBody, &convertOk);
        setInvalidIf(!convertOk, IHttpStatus::BAD_REQUEST_400, "convert body to json failed");
        IToeUtil::setOkAnd(ok, convertOk);
        isJsonInited = true;
    }
    return m_requestJson;
}

QDomNode &IReqRespRaw::getRequestXml(bool *ok)
{
    IToeUtil::setOk(ok, true);
    if(!isXmlInited){
        bool convertOk;
        m_requestXml = IXmlUtil::toXml(m_requestBody, &convertOk);
        setInvalidIf(!ok, IHttpStatus::BAD_REQUEST_400, "convert body to xml failed");
        IToeUtil::setOkAnd(ok, convertOk);
        isXmlInited = true;
    }
    return m_requestXml;
}

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
