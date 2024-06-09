#include "IHeaderJar.h"

#include "core/base/IToeUtil.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/IHttpAssert.h"

$PackageWebCoreBegin

$UseAssert(IHttpAssert)

IHeaderJar::IHeaderJar() : IJarUnit(nullptr)
{
    qFatal(IConstantUtil::UnVisibleMethod);
}

const QMultiHash<IStringView, IStringView>& IHeaderJar::requestHeaders() const
{
    return m_raw->m_requestHeaders;
}

QMultiHash<IStringView, IStringView> &IHeaderJar::requestHeaders()
{
    return m_raw->m_requestHeaders;
}

IStringViewList IHeaderJar::requestHeaderKeys() const
{
    return m_raw->m_requestHeaders.keys();
}

bool IHeaderJar::containRequestHeaderKey(IStringView key) const
{
    return m_raw->m_requestHeaders.contains(key);
}

bool IHeaderJar::containRequestHeaderKey(const QString &key) const
{
    return containRequestHeaderKey(key.toStdString());
}

IStringView IHeaderJar::getRequestHeaderValue(IStringView view) const
{
    return m_raw->m_requestHeaders.value(view);
}

IStringView IHeaderJar::getRequestHeaderValue(const QString &key) const
{
    return getRequestHeaderValue(key.toStdString());
}

IStringViewList IHeaderJar::getRequestHeaderValues(IStringView key) const
{
    return m_raw->m_requestHeaders.values(key);
}

IStringViewList IHeaderJar::getRequestHeaderValues(const QString &key) const
{
    return getRequestHeaderValues(key.toStdString());
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
