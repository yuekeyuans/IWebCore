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

IStringView IWebCore::IJsonResponseContent::getType()
{
    static const std::string type = "IIJsonResponseContent";
    return type;
}

IStringView IWebCore::IJsonResponseContent::getSuggestedMime()
{
    static const std::string mime = IHttpMimeUtil::toString(IHttpMime::APPLICATION_JSON_UTF8).toStdString();
    return mime;
}
