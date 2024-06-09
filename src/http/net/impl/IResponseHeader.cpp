#include "IResponseHeader.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

IResponseHeader::IResponseHeader(IResponseRaw *raw, const QString &key)
    : m_raw(raw), m_key(key)
{
}

IResponseHeader::operator QString() noexcept
{
    return value();
}

const IResponseHeader& IResponseHeader::operator=(const QString &value)
{
    m_raw->headers.emplace(m_key, value);
    return *this;
}

QString IResponseHeader::key()
{
    return m_key;
}

QString IResponseHeader::value()
{
    auto range = m_raw->headers.equal_range(m_key);
    for(auto it = range.first; it != range.second; ++it){
        return it->second;
    }
    return {};
}

QStringList IResponseHeader::values()
{
    QStringList ret;
    auto range = m_raw->headers.equal_range(m_key);
    for(auto it = range.first; it != range.second; ++it){
        ret.append(it->second);
    }
    return ret;
}

$PackageWebCoreEnd
