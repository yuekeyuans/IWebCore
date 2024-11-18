#include "IHttpRequestTimeoutInvalid.h"

$PackageWebCoreBegin

IHttpRequestTimeoutInvalid::IHttpRequestTimeoutInvalid()
    : IHttpInvalidInterface(IHttpStatus::REQUEST_TIMEOUT_408)
{
}

IHttpRequestTimeoutInvalid::IHttpRequestTimeoutInvalid(const QString &description)
    : IHttpInvalidInterface(IHttpStatus::REQUEST_TIMEOUT_408, description)
{
}

$PackageWebCoreEnd
