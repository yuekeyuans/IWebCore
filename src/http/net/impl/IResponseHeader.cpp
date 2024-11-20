#include "IResponseHeader.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

IResponseHeader::IResponseHeader(IResponseRaw& raw, const QString &key)
    : m_raw(raw), m_key(key)
{
}

IResponseHeader::operator QString() noexcept
{
    return value();
}

const IResponseHeader& IResponseHeader::operator=(const QString &value)
{
    m_raw.headers.replace(m_key, value);
    return *this;
}

QString IResponseHeader::key()
{
    return m_key;
}

QString IResponseHeader::value()
{
    return m_raw.headers.value(m_key);
}

QStringList IResponseHeader::values()
{
    return m_raw.headers.values(m_key);
}

$PackageWebCoreEnd
