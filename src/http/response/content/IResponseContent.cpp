#include "IResponseContent.h"

$PackageWebCoreBegin

IResponseContent::~IResponseContent()
{
}

IResponseContent::IResponseContent(const char * data)
    : m_dataRaw(std::string(data))
{
}

IResponseContent::IResponseContent(const QByteArray &byteArray)
    : m_dataRaw(byteArray)
{
}

IResponseContent::IResponseContent(QByteArray &&byteArray) noexcept
    : m_dataRaw(std::move(byteArray))
{
}

IResponseContent::IResponseContent(const std::string &stdString)
    : m_dataRaw(stdString)
{
}

IResponseContent::IResponseContent(std::string &&stdString) noexcept
    : m_dataRaw(std::move(stdString))
{
}

IResponseContent::IResponseContent(IStringView stringView)
    : m_dataRaw(stringView)
{
}

IResponseContent::IResponseContent(IString && data)
    : m_dataRaw(std::move(data))
{
}

IResponseContent::IResponseContent(const IString & data)
    : m_dataRaw(data)
{
}

IStringView IResponseContent::getContent()
{
    return m_dataRaw.m_stringView;
}

$PackageWebCoreEnd
