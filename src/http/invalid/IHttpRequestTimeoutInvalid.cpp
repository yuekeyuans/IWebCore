#include "IHttpRequestTimeoutInvalid.h"

$PackageWebCoreBegin

IHttpRequestTimeoutInvalid::IHttpRequestTimeoutInvalid()
    : IHttpInvalidInterface(IHttpStatusCode::REQUEST_TIMEOUT_408)
{
}

IHttpRequestTimeoutInvalid::IHttpRequestTimeoutInvalid(const QString &description)
    : IHttpInvalidInterface(IHttpStatusCode::REQUEST_TIMEOUT_408, description)
{
}

$PackageWebCoreEnd
