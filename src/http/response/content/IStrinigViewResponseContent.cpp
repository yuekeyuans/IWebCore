#include "IStrinigViewResponseContent.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

IStrinigViewResponseContent::IStrinigViewResponseContent(IStringView value)
    : IResponseContentWare(value)
{
}

const std::string& IStrinigViewResponseContent::getType()
{
    return CLASS_NAME;
}

const std::string& IStrinigViewResponseContent::getSuggestedMime() const
{
    static const std::string mime = IHttpMimeUtil::toString(IHttpMime::TEXT_PLAIN_UTF8);
    return mime;
}

$PackageWebCoreEnd
