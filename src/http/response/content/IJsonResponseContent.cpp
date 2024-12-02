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
