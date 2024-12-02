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

$PackageWebCoreEnd
