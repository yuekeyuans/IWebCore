#include "IHttpInvalidWare.h"

$PackageWebCoreBegin

IWebCore::IHttpInvalidWare::IHttpInvalidWare(IHttpStatusCode status, const QString &name_, const QString &description_)
    :status(status), name(name_), description(description_)
{
    invalid = !name.isEmpty();
}

$PackageWebCoreEnd
