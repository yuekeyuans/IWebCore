#include "IStdStringResponseContent.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

IStdStringResponseContent::IStdStringResponseContent(std::string &&value)
    : m_content(std::move(value))
{
}

IStdStringResponseContent::IStdStringResponseContent(const std::string & value)
    : m_content(value)
{
}

int IStdStringResponseContent::getSize()
{
    return m_content.length();
}

IStringView IStdStringResponseContent::getType()
{
    static const std::string type = "IStdStringResponseContent";
    return type;
}

IStringView IStdStringResponseContent::getContent()
{
    return IStringView(m_content);
}

IStringView IStdStringResponseContent::getSuggestedMime()
{
    static const std::string mime = IHttpMimeUtil::toString(IHttpMime::TEXT_PLAIN_UTF8).toStdString();
    return mime;
}

$PackageWebCoreEnd
