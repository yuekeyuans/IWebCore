#include "IHttpRequestHeaderFieldTooLargeInvalid.h"

$PackageWebCoreBegin

IHttpRequestHeaderFieldTooLargeInvalid::IHttpRequestHeaderFieldTooLargeInvalid(const std::string &description)
    : IHttpInvalidInterface(IHttpStatus::REQUEST_HEADER_FIELDS_TOO_LARGE_431, description)
{
}

$PackageWebCoreEnd
