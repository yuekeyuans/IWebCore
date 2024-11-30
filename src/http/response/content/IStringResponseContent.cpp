#include "IStringResponseContent.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

IStringResponseContent::IStringResponseContent(IString && value)
    : IResponseContentWare(std::move(value))
{
}

IStringResponseContent::IStringResponseContent(const IString & value)
    : IResponseContentWare(value)
{
}

const std::string &IStringResponseContent::getType() const
{
    return CLASS_NAME;
}

const std::string &IStringResponseContent::getSuggestedMime() const
{
    static const std::string& mime = IHttpMimeUtil::toString(IHttpMime::TEXT_PLAIN_UTF8).m_stringView.toStdString();
    return mime;
}

$PackageWebCoreEnd
