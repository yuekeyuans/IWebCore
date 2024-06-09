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

const std::unordered_multimap<QString, QString> &IHeaderJar::responseHeaders() const
{
    return m_raw->m_responseRaw->headers;
}

std::unordered_multimap<QString, QString> &IHeaderJar::responseHeaders()
{
    return m_raw->m_responseRaw->headers;
}

QStringList IHeaderJar::responseHeaderKeys() const
{
    QStringList ret;
    const auto headers = m_raw->m_responseRaw->headers;
    for(auto it=headers.cbegin(); it!= headers.cend(); it++){
        if(!ret.contains(it->first)){
            ret.append(it->first);
        }
    }
    return ret;
}

bool IHeaderJar::containResponseHeaderKey(const QString &key) const
{
    auto range = m_raw->m_responseRaw->headers.equal_range(key);
    return range.first != range.second;
}

// NOTE: 注意这两者之间的差别， setReponseHeader是，如果有这个值，就替换， addResponseHeader 表示不管怎样，直接添加。
void IHeaderJar::addResponseHeader(QString key, QString value)
{
    m_raw->m_responseRaw->headers.emplace(std::move(key), std::move(value));
}

void IHeaderJar::addResponseHeader(QString key, const QStringList &values)
{
    for(const auto& value : values){
        m_raw->m_responseRaw->headers.emplace(std::move(key), value);
    }
}

void IHeaderJar::setResponseHeader(QString key, QString value)
{
    deleteReponseHeader(key);
    m_raw->m_responseRaw->headers.emplace(std::move(key), std::move(value));
}

void IHeaderJar::setResponseHeader(QString key, const QStringList &values)
{
    deleteReponseHeader(key);
    for(const auto& value : values){
        m_raw->m_responseRaw->headers.emplace(key, value);
    }
}

void IHeaderJar::deleteReponseHeader(const QString &key)
{
    auto range = m_raw->m_responseRaw->headers.equal_range(key);
    for(auto it=range.first; it!= range.second; it++){
        m_raw->m_responseRaw->headers.erase(it);
    }
}

$PackageWebCoreEnd
