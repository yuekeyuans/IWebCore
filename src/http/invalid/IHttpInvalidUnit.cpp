#include "IHttpInvalidUnit.h"

$PackageWebCoreBegin

IWebCore::IHttpInvalidUnit::IHttpInvalidUnit(IHttpStatusCode status, const QString &tag, const QString &description)
    :status(status), tag(tag), description(description)
{
}

$PackageWebCoreEnd
