#include "IHttpNotFoundInvalid.h"

$PackageWebCoreBegin

IHttpNotFoundInvalid::IHttpNotFoundInvalid()
    : IHttpInvalidInterface(IHttpStatus::NOT_FOUND_404)
{
}

IHttpNotFoundInvalid::IHttpNotFoundInvalid(const QString& description)
    : IHttpInvalidInterface(IHttpStatus::NOT_FOUND_404, description)
{
}

$PackageWebCoreEnd
