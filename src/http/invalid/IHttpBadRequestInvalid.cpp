#include "IHttpBadRequestInvalid.h"

$PackageWebCoreBegin

IHttpBadRequestInvalid::IHttpBadRequestInvalid()
    : IHttpInvalidInterface(IHttpStatus::BAD_REQUEST_400)
{
}

IHttpBadRequestInvalid::IHttpBadRequestInvalid(const std::string &description)
    : IHttpInvalidInterface(IHttpStatus::BAD_REQUEST_400, description)
{
}

$PackageWebCoreEnd
