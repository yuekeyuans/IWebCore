#include "IResponseHeaderRef.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

IResponseHeaderRef::IResponseHeaderRef(IResponseRaw *raw, const QString &key, const QString &value)
    : m_raw(raw), m_key(key), m_value(value)
{
}

const IResponseHeaderRef& IResponseHeaderRef::operator=(const QString &value)
{
    m_value = value;
    m_raw->headers.insert(m_key, m_value);
    return *this;
}

IResponseHeaderRef::operator QString() noexcept
{
    return m_value;
}

$PackageWebCoreEnd
