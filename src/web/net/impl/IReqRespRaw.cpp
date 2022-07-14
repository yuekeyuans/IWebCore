#include "IReqRespRaw.h"
#include "base/IHeaderUtil.h"
#include "base/IConstantUtil.h"
#include "base/IToeUtil.h"
#include "base/IJsonUtil.h"
#include "base/IXmlUtil.h"

$PackageWebCoreBegin

IReqRespRaw::IReqRespRaw()
{
    m_headerJar.raw = this;
    m_cookieJar.raw = this;
}

bool IReqRespRaw::valid() const
{
    return this->m_valid;
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

void IReqRespRaw::setInvalid(IHttpStatus status, const QString &message)
{
    this->m_valid = false;
    this->m_responseMime = IHttpMimeHelper::toString(IHttpMime::TEXT_PLAIN_UTF8);
    this->m_responseStatus = status;

    QString tip = IHttpStatusHelper::toString(status).append(" - ")
                      .append(IHttpStatusHelper::toStringDescription(status)).append(": ")
                      .append(message).append(IConstantUtil::NewLine);
    this->m_responseContent = tip.toUtf8();
}

$PackageWebCoreEnd
