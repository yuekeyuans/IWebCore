#include "IHeaderJar.h"
#include "core/abort/IGlobalAbort.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/net/impl/IRequestImpl.h"

$PackageWebCoreBegin

IHeaderJar::IHeaderJar() : IJarUnit()
{
    IGlobalAbort::abortUnVisibleMethod();
}

//const QMultiHash<IStringView, IStringView>& IHeaderJar::requestHeaders() const
//{
//    return m_impl.m_reqRaw.m_requestHeaders;
//}

//QMultiHash<IStringView, IStringView> &IHeaderJar::requestHeaders()
//{
//    return m_impl.m_reqRaw.m_requestHeaders;
//}

std::vector<IString> IHeaderJar::requestHeaderKeys() const
{
    return m_impl.m_reqRaw.m_requestHeaders.keys();
}

bool IHeaderJar::containRequestHeaderKey(IStringView key) const
{
    return m_impl.m_reqRaw.m_requestHeaders.hasKey(key);
}

bool IHeaderJar::containRequestHeaderKey(const QString &key) const
{
    auto temp = key.toUtf8();
    return containRequestHeaderKey(IStringView(temp));
}

IString IHeaderJar::getRequestHeaderValue(IStringView view) const
{
    return m_impl.m_reqRaw.m_requestHeaders.value(view);
}

IString IHeaderJar::getRequestHeaderValue(const QString &key) const
{
    auto temp = key.toUtf8();
    return getRequestHeaderValue(IStringView(temp));
}

const std::vector<IString>& IHeaderJar::getRequestHeaderValues(IStringView key) const
{
    return m_impl.m_reqRaw.m_requestHeaders.values(key);
}

const std::vector<IString>& IHeaderJar::getRequestHeaderValues(const QString &key) const
{
    auto temp = key.toUtf8();
    return getRequestHeaderValues(IStringView(temp));
}

const QMultiHash<QString, QString> &IHeaderJar::responseHeaders() const
{
    return m_impl.m_respRaw.m_headers;
}

QMultiHash<QString, QString> &IHeaderJar::responseHeaders()
{
    return m_impl.m_respRaw.m_headers;
}

QStringList IHeaderJar::responseHeaderKeys() const
{
    return m_impl.m_respRaw.m_headers.keys();
}

bool IHeaderJar::containResponseHeaderKey(const QString &key) const
{
    auto range = m_impl.m_respRaw.m_headers.equal_range(key);
    return range.first != range.second;
}

// NOTE: 注意这两者之间的差别， setReponseHeader是，如果有这个值，就替换， addResponseHeader 表示不管怎样，直接添加。
void IHeaderJar::addResponseHeader(QString key, QString value)
{
    m_impl.m_respRaw.m_headers.insertMulti(std::move(key), std::move(value));
}

void IHeaderJar::addResponseHeader(QString key, const QStringList &values)
{
    for(const auto& value : values){
        m_impl.m_respRaw.m_headers.insertMulti(std::move(key), value);
    }
}

void IHeaderJar::setResponseHeader(QString key, QString value)
{
    deleteReponseHeader(key);
    m_impl.m_respRaw.m_headers.insert(std::move(key), std::move(value));
}

void IHeaderJar::setResponseHeader(QString key, const QStringList &values)
{
    deleteReponseHeader(key);
    for(const auto& value : values){
        m_impl.m_respRaw.m_headers.insert(key, value);
    }
}

// TODO: 这里 HEADERS 重构时再做吧
void IHeaderJar::setResponseHeader(QString key, const IString & value)
{
    deleteReponseHeader(key);
//    for(const auto& value : values){
//    m_impl.m_respRaw.m_headers.insert(key, value.toStringView().toStdString());
//    }
}

void IHeaderJar::deleteReponseHeader(const QString &key)
{
    auto& headers = m_impl.m_respRaw.m_headers;
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
