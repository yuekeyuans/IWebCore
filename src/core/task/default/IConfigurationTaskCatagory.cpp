#include "IConfigurationTaskCatagory.h"

$PackageWebCoreBegin

QString IConfigurationTaskCatagory::name() const
{
    return "Configuration";
}

double IConfigurationTaskCatagory::order() const
{
    return  1;
}

$PackageWebCoreEnd
