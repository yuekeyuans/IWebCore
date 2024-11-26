#include "IStrinigViewResponseContent.h"
#include "http/biscuits/IHttpMime.h"

IStrinigViewResponseContent::IStrinigViewResponseContent(IStringView value)
    : IResponseContentWare(value)
{
}

IStringView IStrinigViewResponseContent::getType()
{
    static const std::string type = "IIStrinigViewResponseContent";
    return type;
}

IStringView IStrinigViewResponseContent::getSuggestedMime()
{
    static const std::string mime = IHttpMimeUtil::toString(IHttpMime::TEXT_PLAIN_UTF8).toStdString();
    return mime;
}
