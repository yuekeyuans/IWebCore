#include "IStartupTaskCatagory.h"

$PackageWebCoreBegin

QString IStartupTaskCatagory::name() const
{
    return "StartUp";
}

double IStartupTaskCatagory::order() const
{
    return 0.5;
}

$PackageWebCoreEnd
