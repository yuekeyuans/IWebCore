#include "IHeaderJar.h"
#include "core/abort/IGlobalAbort.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/net/impl/IRequestImpl.h"

$PackageWebCoreBegin

std::vector<IStringView> IHeaderJar::requestHeaderKeys() const
{
    return m_impl.m_reqRaw.m_requestHeaders.keys();
}

bool IHeaderJar::containRequestHeaderKey(const IString& key) const
{
    return m_impl.m_reqRaw.m_requestHeaders.contain(key);
}

IString IHeaderJar::getRequestHeaderValue(const IString& view) const
{
    return m_impl.m_reqRaw.m_requestHeaders.value(view);
}

const std::vector<IString>& IHeaderJar::getRequestHeaderValues(const IString& key) const
{
    return m_impl.m_reqRaw.m_requestHeaders.values(key);
}

IHttpHeader &IHeaderJar::responseHeaders()
{
    return m_impl.m_respRaw.m_headers;
}

std::vector<IStringView> IHeaderJar::responseHeaderKeys() const
{
    return m_impl.m_respRaw.m_headers.keys();
}

bool IHeaderJar::containResponseHeaderKey(const IString &key) const
{
    return m_impl.m_respRaw.m_headers.contain(key);
}

// NOTE: 注意这两者之间的差别， setReponseHeader是，如果有这个值，就替换， addResponseHeader 表示不管怎样，直接添加。
void IHeaderJar::addResponseHeader(IString key, IString value)
{
    m_impl.m_respRaw.m_headers.insert(std::move(key), std::move(value));
}

void IHeaderJar::addResponseHeader(IString key, const QStringList &values)
{
    for(const auto& value : values){
        m_impl.m_respRaw.m_headers.insert(key, value.toStdString());
    }
}

void IHeaderJar::setResponseHeader(IString key, IString value)
{
    deleteReponseHeader(key);
    m_impl.m_respRaw.m_headers.insert(std::move(key), std::move(value));
}

void IHeaderJar::setResponseHeader(IString key, const QStringList &values)
{
    deleteReponseHeader(key);
    for(const auto& value : values){
        m_impl.m_respRaw.m_headers.insert(key, value.toStdString());
    }
}

// TODO: 这里 HEADERS 重构时再做吧
//void IHeaderJar::setResponseHeader(IString key, const IString & value)
//{
//    deleteReponseHeader(key);
////    for(const auto& value : values){
////    m_impl.m_respRaw.m_headers.insert(key, value.toStringView().toStdString());
////    }
//}

void IHeaderJar::deleteReponseHeader(const IString &key)
{
    m_impl.m_respRaw.m_headers.clear(key);
}

$PackageWebCoreEnd
