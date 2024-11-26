#include "IResponseContentWare.h"

$PackageWebCoreBegin

IResponseContentWare::~IResponseContentWare()
{
    if(m_excess){
        delete m_excess;
        m_excess = nullptr;
    }
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

IResponseContentWare::IResponseContentWare(IStringData && data)
    : m_dataRaw(std::move(data))
{
}

IResponseContentWare::IResponseContentWare(const IStringData & data)
    : m_dataRaw(data)
{
}

int IResponseContentWare::getSize()
{
    return m_dataRaw.toStringView().length();
}

IStringView IResponseContentWare::getContent()
{
    return m_dataRaw.toStringView();
}

$PackageWebCoreEnd
