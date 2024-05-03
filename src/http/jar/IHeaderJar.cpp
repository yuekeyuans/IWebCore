#include "IHeaderJar.h"

#include "core/base/IToeUtil.h"
#include "http/net/impl/IReqRespRaw.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/IHttpAssert.h"

$PackageWebCoreBegin

$UseAssert(IHttpAssert)

IHeaderJar::IHeaderJar() : IJarUnit(nullptr)
{
    qFatal(IConstantUtil::UnVisibleMethod);
}

const QList<QPair<QString, QString>>& IHeaderJar::requestHeaders() const
{
    return m_raw->m_requestHeaders;
}

QList<QPair<QString, QString> > &IHeaderJar::requestHeaders()
{
    return m_raw->m_requestHeaders;
}

QStringList IHeaderJar::requestHeaderKeys() const
{
    QStringList ret;
    for(const auto& pair : m_raw->m_requestHeaders){
        if(!ret.contains(pair.first)){
            ret.append(pair.first);
        }
    }
    return ret;
}

bool IHeaderJar::containRequestHeaderKey(const QString &key) const
{
    for(const auto& pair : m_raw->m_requestHeaders){
        if(pair.first == key){
            return true;
        }
    }
    return false;
}

QString IHeaderJar::getRequestHeaderValue(const QString &key, bool& ok) const
{
    for(const auto& pair : m_raw->m_requestHeaders){
        if(pair.first == key){
            IToeUtil::setOk(ok, true);
            return pair.second;
        }
    }
    IToeUtil::setOk(ok, false);
    return "";
}

QStringList IHeaderJar::getRequestHeaderValues(const QString &key) const
{
    QStringList ret;
    for(const auto& pair : m_raw->m_requestHeaders){
        if(pair.first == key){
            ret.append(pair.second);
        }
    }
    return ret;
}

const QMultiHash<QString, QString> &IHeaderJar::responseHeaders() const
{
    return m_raw->m_responseRaw->headers;
}

QMultiHash<QString, QString> &IHeaderJar::responseHeaders()
{
    return m_raw->m_responseRaw->headers;
}

QStringList IHeaderJar::responseHeaderKeys() const
{
    return m_raw->m_responseRaw->headers.keys();
}

bool IHeaderJar::containResponseHeaderKey(const QString &key) const
{
    return m_raw->m_responseRaw->headers.contains(key);
}

QString IHeaderJar::getResponseHeaderValue(const QString &key, bool& ok) const
{
    for(const auto& pair : m_raw->m_requestHeaders){
        if(pair.first == key){
            IToeUtil::setOk(ok, true);
            return pair.second;
        }
    }
    IToeUtil::setOk(ok, false);
    return "";
}

QStringList IHeaderJar::getResponseHeaderValues(const QString &key) const
{
    return m_raw->m_responseRaw->headers.values(key);
}

// NOTE: 注意这两者之间的差别， setReponseHeader是，如果有这个值，就替换， addResponseHeader 表示不管怎样，直接添加。
void IHeaderJar::addResponseHeader(const QString &key, const QString &value)
{
    m_raw->m_responseRaw->headers.insertMulti(key, value);
}

void IHeaderJar::addResponseHeader(const QString &key, const QStringList &values)
{
    for(const auto& value : values){
        m_raw->m_responseRaw->headers.insert(key, value);
    }
}

void IHeaderJar::setResponseHeader(const QString &key, const QString &value)
{
    m_raw->m_responseRaw->headers.insert(key, value);
}

void IHeaderJar::setResponseHeader(const QString &key, const QStringList &values)
{
    m_raw->m_responseRaw->headers.remove(key);
    for(const auto& value : values){
        m_raw->m_responseRaw->headers.insert(key, value);
    }
}

void IHeaderJar::deleteReponseHeader(const QString &key)
{
    m_raw->m_responseRaw->headers.remove(key);
}

$PackageWebCoreEnd
