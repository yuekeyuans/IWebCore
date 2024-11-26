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

IStringView IStdStringResponseContent::getType()
{
    static const std::string type = "IStdStringResponseContent";
    return type;
}

IStringView IStdStringResponseContent::getSuggestedMime()
{
    static const std::string mime = IHttpMimeUtil::toString(IHttpMime::TEXT_PLAIN_UTF8).toStdString();
    return mime;
}

$PackageWebCoreEnd
