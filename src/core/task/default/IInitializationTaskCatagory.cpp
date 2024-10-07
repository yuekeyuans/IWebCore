#include "IInitializationTaskCatagory.h"

$PackageWebCoreBegin

const char* IInitializationTaskCatagory::$catagory() const
{
    return "Initialization";
}

double IInitializationTaskCatagory::$order() const
{
    return 2;
}

$PackageWebCoreEnd
