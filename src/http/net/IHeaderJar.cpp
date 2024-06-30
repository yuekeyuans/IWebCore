#include "IHeaderJar.h"

#include "core/util/IToeUtil.h"
#include "core/abort/IGlobalAbort.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

IHeaderJar::IHeaderJar() : IJarUnit(nullptr)
{
    IGlobalAbort::abortUnVisibleMethod();
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
    auto temp = key.toUtf8();
    return containRequestHeaderKey(IStringView(temp));
}

IStringView IHeaderJar::getRequestHeaderValue(IStringView view) const
{
    return m_raw->m_requestHeaders.value(view);
}

IStringView IHeaderJar::getRequestHeaderValue(const QString &key) const
{
    auto temp = key.toUtf8();
    return getRequestHeaderValue(IStringView(temp));
}

IStringViewList IHeaderJar::getRequestHeaderValues(IStringView key) const
{
    return m_raw->m_requestHeaders.values(key);
}

IStringViewList IHeaderJar::getRequestHeaderValues(const QString &key) const
{
    auto temp = key.toUtf8();
    return getRequestHeaderValues(IStringView(temp));
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
    auto range = m_raw->m_responseRaw->headers.equal_range(key);
    return range.first != range.second;
}

// NOTE: 注意这两者之间的差别， setReponseHeader是，如果有这个值，就替换， addResponseHeader 表示不管怎样，直接添加。
void IHeaderJar::addResponseHeader(QString key, QString value)
{
    m_raw->m_responseRaw->headers.insertMulti(std::move(key), std::move(value));
}

void IHeaderJar::addResponseHeader(QString key, const QStringList &values)
{
    for(const auto& value : values){
        m_raw->m_responseRaw->headers.insertMulti(std::move(key), value);
    }
}

void IHeaderJar::setResponseHeader(QString key, QString value)
{
    deleteReponseHeader(key);
    m_raw->m_responseRaw->headers.insert(std::move(key), std::move(value));
}

void IHeaderJar::setResponseHeader(QString key, const QStringList &values)
{
    deleteReponseHeader(key);
    for(const auto& value : values){
        m_raw->m_responseRaw->headers.insert(key, value);
    }
}

void IHeaderJar::deleteReponseHeader(const QString &key)
{
    auto& headers = m_raw->m_responseRaw->headers;
    auto i = headers.find(key);
    while (i != headers.end() && i.key() == key) {
        if (i.value() == 0) {
            i = headers.erase(i);
        } else {
            ++i;
        }
    }
}

$PackageWebCoreEnd
