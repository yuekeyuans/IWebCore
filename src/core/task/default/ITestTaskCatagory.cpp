#include "ITestTaskCatagory.h"

$PackageWebCoreBegin

QString IWebCore::ITestTaskCatagory::name() const
{
    return "Test";
}

double IWebCore::ITestTaskCatagory::order() const
{
    return 99;
}

bool ITestTaskCatagory::isCatagoryDefaultEnabled() const
{
    return false;
}

$PackageWebCoreEnd
