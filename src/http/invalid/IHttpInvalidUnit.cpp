#include "IHttpInvalidUnit.h"

$PackageWebCoreBegin

IWebCore::IHttpInvalidUnit::IHttpInvalidUnit(IHttpStatusCode status, const QString &tag_, const QString &description_)
    :status(status), tag(tag_), description(description_)
{
    invalid = !tag.isEmpty();
}

$PackageWebCoreEnd
