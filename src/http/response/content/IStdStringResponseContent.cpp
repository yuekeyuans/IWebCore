#include "IStdStringResponseContent.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

IStdStringResponseContent::IStdStringResponseContent(std::string &&value)
    : IResponseContentWare(std::move(value))
{
}

IStdStringResponseContent::IStdStringResponseContent(const std::string & value)
    : IResponseContentWare(value)
{
}

const std::string& IStdStringResponseContent::getType() const
{
    return CLASS_NAME;
}

const std::string& IStdStringResponseContent::getSuggestedMime() const
{
    static const std::string& mime = IHttpMimeUtil::toString(IHttpMime::TEXT_PLAIN_UTF8);
    return mime;
}

$PackageWebCoreEnd
