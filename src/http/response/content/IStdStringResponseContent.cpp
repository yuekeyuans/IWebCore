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

const char *IStdStringResponseContent::getType()
{
    return "stdString";
}

IStringView IStdStringResponseContent::getContent()
{
    return IStringView(m_content);
}

QString IStdStringResponseContent::getSuggestedMime()
{
    return IHttpMimeUtil::toString(IHttpMime::TEXT_PLAIN_UTF8);
}

$PackageWebCoreEnd
