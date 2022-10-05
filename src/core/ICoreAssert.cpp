#include "ICoreAssert.h"

$PackageWebCoreBegin

void ICoreAssert::loadFromFunction()
{
    // IApplication
    addFatal("IApplication_not_created", "you can not get any IApplication instance when IApplication not created");
}

$PackageWebCoreEnd
