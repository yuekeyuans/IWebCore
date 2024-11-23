#include "IIStrinigViewResponseContent.h"
#include "http/biscuits/IHttpMime.h"

IIStrinigViewResponseContent::IIStrinigViewResponseContent(IStringView value)
    : m_content(value)
{
}

int IIStrinigViewResponseContent::getSize()
{
    return m_content.length();
}

IStringView IIStrinigViewResponseContent::getType()
{
    static const std::string type = "IIStrinigViewResponseContent";
    return type;
}

IStringView IIStrinigViewResponseContent::getContent()
{
    return m_content;
}

IStringView IIStrinigViewResponseContent::getSuggestedMime()
{
    static const std::string mime = IHttpMimeUtil::toString(IHttpMime::TEXT_PLAIN_UTF8).toStdString();
    return mime;
}
