#include "IStartupTaskCatagory.h"

$PackageWebCoreBegin

const char* IStartupTaskCatagory::$catagory() const
{
    return "StartUp";
}

double IStartupTaskCatagory::$order() const
{
    return 1;
}

$PackageWebCoreEnd
