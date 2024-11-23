#include "IIJsonResponseContent.h"
#include "http/biscuits/IHttpMime.h"


IIJsonResponseContent::IIJsonResponseContent(IJson && data)
    : m_content(std::move(data))
{
    m_data = m_content.dump();
}

IIJsonResponseContent::IIJsonResponseContent(const IJson &data)
    : m_content(data)
{
    m_data = m_content.dump();
}

IIJsonResponseContent::IIJsonResponseContent(std::string && data)
    : m_data(std::move(data))
{
}

IIJsonResponseContent::IIJsonResponseContent(const std::string & data)
    : m_data(data)
{
}

int IWebCore::IIJsonResponseContent::getSize()
{
    return m_data.length();
}

IStringView IWebCore::IIJsonResponseContent::getType()
{
    static const std::string type = "IIJsonResponseContent";
    return type;
}

IStringView IWebCore::IIJsonResponseContent::getContent()
{
    return m_data;
}

IStringView IWebCore::IIJsonResponseContent::getSuggestedMime()
{
    static const std::string mime = IHttpMimeUtil::toString(IHttpMime::APPLICATION_JSON_UTF8).toStdString();
    return mime;
}
