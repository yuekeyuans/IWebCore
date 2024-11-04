#include "IHttpInternalErrorInvalid.h"

$PackageWebCoreBegin

IHttpInternalErrorInvalid::IHttpInternalErrorInvalid()
    : IHttpInvalidInterface(IHttpStatus::INTERNAL_SERVER_ERROR_500)
{
}

IHttpInternalErrorInvalid::IHttpInternalErrorInvalid(const QString &description)
    : IHttpInvalidInterface(IHttpStatus::INTERNAL_SERVER_ERROR_500, description)
{
}

$PackageWebCoreEnd
