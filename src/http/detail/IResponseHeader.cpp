#include "IResponseHeader.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

IResponseHeader::IResponseHeader(IResponseRaw& raw, const IString &key)
    : m_raw(raw), m_key(key)
{
    m_key.solidify();
}

IResponseHeader::operator IStringView () noexcept
{
    return value();
}

//const IResponseHeader& IResponseHeader::operator=(const IString &value)
//{
//    m_raw.m_headers.insert(m_key, value);
//    return *this;
//}

IStringView IResponseHeader::key()
{
    return m_key.m_view;
}

IStringView IResponseHeader::value()
{
    return m_raw.m_headers.value(m_key.m_view);
}

$PackageWebCoreEnd
