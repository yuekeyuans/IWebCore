#include "IHttpNotFoundInvalid.h"

$PackageWebCoreBegin

IHttpNotFoundInvalid::IHttpNotFoundInvalid()
    : IHttpInvalidInterface(IHttpStatus::NOT_FOUND_404)
{
}

IHttpNotFoundInvalid::IHttpNotFoundInvalid(QString description)
    : IHttpInvalidInterface(IHttpStatus::NOT_FOUND_404, description)
{
}

$PackageWebCoreEnd
