#include "ICoreAssert.h"

$PackageWebCoreBegin

void ICoreAssert::loadFromFunction()
{
    // IApplication
    addFatal("IApplication_not_created", "you can not get any IApplication instance when IApplication not created");
    addFatal("IApplication_should_not_created_twice", "you can not create IApplication instance twice, since IApplication should only exist one in one process");

}

$PackageWebCoreEnd
