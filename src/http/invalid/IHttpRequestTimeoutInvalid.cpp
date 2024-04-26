#include "IHttpRequestTimeoutInvalid.h"

$PackageWebCoreBegin

IHttpRequestTimeoutInvalid::IHttpRequestTimeoutInvalid(const QString &description)
    : IHttpInvalidInterface(IHttpStatusCode::REQUEST_TIMEOUT_408, description)
{
}

$PackageWebCoreEnd
