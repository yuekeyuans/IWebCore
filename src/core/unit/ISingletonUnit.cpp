#include "ISingletonUnit.h"
#include "core/assert/IGlobalAbort.h"

$PackageWebCoreBegin


void ISingletonUnitDetail::abortError(QString content)
{
    IGlobalAbort::abortSingletonInstanceCreateError(content);
}

$PackageWebCoreEnd
