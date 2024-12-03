#include "IStringResponseContent.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

IStringResponseContent::IStringResponseContent(IString && value)
    : IResponseContent(std::move(value))
{
}

IStringResponseContent::IStringResponseContent(const IString & value)
    : IResponseContent(value)
{
}

$PackageWebCoreEnd
