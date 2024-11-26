#include "IJsonResponseContent.h"
#include "http/biscuits/IHttpMime.h"


IJsonResponseContent::IJsonResponseContent(IJson && data)
    : IResponseContentWare(data.dump())
{
}

IJsonResponseContent::IJsonResponseContent(const IJson &data)
    : IResponseContentWare(data.dump())
{
}

IJsonResponseContent::IJsonResponseContent(std::string && data)
    : IResponseContentWare(std::move(data))
{
}

IJsonResponseContent::IJsonResponseContent(const std::string & data)
    : IResponseContentWare(data)
{
}

const std::string& IWebCore::IJsonResponseContent::getType()
{
    return CLASS_NAME;
}

const std::string& IWebCore::IJsonResponseContent::getSuggestedMime() const
{
    static const std::string& mime = IHttpMimeUtil::toString(IHttpMime::APPLICATION_JSON_UTF8);
    return mime;
}
