#include "IHttpInternalErrorInvalid.h"

$PackageWebCoreBegin

IHttpInternalErrorInvalid::IHttpInternalErrorInvalid(const QString &description)
    : IHttpInvalidInterface(IHttpStatus::INTERNAL_SERVER_ERROR_500, description)
{
}

$PackageWebCoreEnd
