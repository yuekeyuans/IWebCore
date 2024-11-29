#include "IResponseHeader.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

IResponseHeader::IResponseHeader(IResponseRaw& raw, const IString &key)
    : m_raw(raw), m_key(key)
{
}

IResponseHeader::operator const IString&() noexcept
{
    return value();
}

const IResponseHeader& IResponseHeader::operator=(const IString &value)
{
    m_raw.m_headers.replace(m_key, value);
    return *this;
}

const IString& IResponseHeader::key()
{
    return m_key;
}

const IString& IResponseHeader::value()
{
    return m_raw.m_headers.value(m_key);
}

const std::vector<IString> & IResponseHeader::values()
{
    return m_raw.m_headers.values(m_key);
}

$PackageWebCoreEnd
