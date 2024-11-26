#include "IHttpRequestTimeoutInvalid.h"

$PackageWebCoreBegin

IHttpRequestTimeoutInvalid::IHttpRequestTimeoutInvalid()
    : IHttpInvalidInterface(IHttpStatus::REQUEST_TIMEOUT_408)
{
}

IHttpRequestTimeoutInvalid::IHttpRequestTimeoutInvalid(const std::string &description)
    : IHttpInvalidInterface(IHttpStatus::REQUEST_TIMEOUT_408, description)
{
}

$PackageWebCoreEnd
