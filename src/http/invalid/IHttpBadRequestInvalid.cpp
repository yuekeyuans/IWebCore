#include "IHttpBadRequestInvalid.h"

$PackageWebCoreBegin

IHttpBadRequestInvalid::IHttpBadRequestInvalid(const QString &description)
    : IHttpInvalidInterface(IHttpStatus::BAD_REQUEST_400, description)
{
}

$PackageWebCoreEnd
