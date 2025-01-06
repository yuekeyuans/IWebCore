#include "IHeaderJar.h"
#include "core/abort/IGlobalAbort.h"
#include "core/util/IConstantUtil.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/net/impl/IRequestImpl.h"

$PackageWebCoreBegin

std::vector<IStringView> IHeaderJar::requestHeaderKeys() const
{
    std::vector<IStringView> ret;
    const auto& headers = m_impl.m_reqRaw.m_headers;
    for(auto it=headers.begin(); it!= headers.end(); it++){
        ret.push_back(it.key());
    }
    return ret;
}

bool IHeaderJar::containRequestHeaderKey(const IString& key) const
{
    const auto& keys = requestHeaderKeys();
    return std::find_if(keys.begin(), keys.end(), [&](IStringView data){
        return data.equalIgnoreCase(key.m_view);
    }) != keys.end();
}

IStringView IHeaderJar::getRequestHeaderValue(const IString& view) const
{
    const auto& headers = m_impl.m_reqRaw.m_headers;
    for(auto it=headers.begin(); it!= headers.end(); it++){
        if(it.key().equalIgnoreCase(view)){
            return it.value();
        }
    }

    return IConstantUtil::Empty;
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
    m_impl.m_respRaw.m_headers.remove(key);
}

$PackageWebCoreEnd
