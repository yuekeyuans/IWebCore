#include "IResponseContentWare.h"

$PackageWebCoreBegin

IResponseContentWare::~IResponseContentWare()
{
}

IResponseContentWare::IResponseContentWare(const QByteArray &byteArray)
    : m_dataRaw(byteArray)
{
}

IResponseContentWare::IResponseContentWare(QByteArray &&byteArray) noexcept
    : m_dataRaw(std::move(byteArray))
{
}

IResponseContentWare::IResponseContentWare(const std::string &stdString)
    : m_dataRaw(stdString)
{
}

IResponseContentWare::IResponseContentWare(std::string &&stdString) noexcept
    : m_dataRaw(std::move(stdString))
{
}

IResponseContentWare::IResponseContentWare(IStringView stringView)
    : m_dataRaw(stringView)
{
}

IResponseContentWare::IResponseContentWare(IString && data)
    : m_dataRaw(std::move(data))
{
}

IResponseContentWare::IResponseContentWare(const IString & data)
    : m_dataRaw(data)
{
}

IStringView IResponseContentWare::getContent()
{
    return m_dataRaw.m_stringView;
}

$PackageWebCoreEnd
