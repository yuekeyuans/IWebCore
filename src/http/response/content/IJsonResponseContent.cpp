#include "IJsonResponseContent.h"
#include "http/biscuits/IHttpMime.h"


IJsonResponseContent::IJsonResponseContent(IJson && data)
    : m_content(std::move(data))
{
    m_data = m_content.dump();
}

IJsonResponseContent::IJsonResponseContent(const IJson &data)
    : m_content(data)
{
    m_data = m_content.dump();
}

IJsonResponseContent::IJsonResponseContent(std::string && data)
    : m_data(std::move(data))
{
}

IJsonResponseContent::IJsonResponseContent(const std::string & data)
    : m_data(data)
{
}

int IWebCore::IJsonResponseContent::getSize()
{
    return m_data.length();
}

IStringView IWebCore::IJsonResponseContent::getType()
{
    static const std::string type = "IIJsonResponseContent";
    return type;
}

IStringView IWebCore::IJsonResponseContent::getContent()
{
    return m_data;
}

IStringView IWebCore::IJsonResponseContent::getSuggestedMime()
{
    static const std::string mime = IHttpMimeUtil::toString(IHttpMime::APPLICATION_JSON_UTF8).toStdString();
    return mime;
}
