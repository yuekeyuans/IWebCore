#include "ISingletonUnit.h"
#include "core/abort/IGlobalAbort.h"

$PackageWebCoreBegin

void ISingletonUnitDetail::abortError(QString content)
{
    IGlobalAbort::abortSingletonInstanceCreateError(content);
}

$PackageWebCoreEnd
