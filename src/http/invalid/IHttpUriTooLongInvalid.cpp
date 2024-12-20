#include "IHttpUriTooLongInvalid.h"

$PackageWebCoreBegin

IHttpUriTooLongInvalid::IHttpUriTooLongInvalid()
    : IHttpInvalidInterface(IHttpStatus::URI_TOO_LONG_414)
{
}

IHttpUriTooLongInvalid::IHttpUriTooLongInvalid(const std::string &description)
    : IHttpInvalidInterface(IHttpStatus::URI_TOO_LONG_414, description)
{
}

$PackageWebCoreEnd
