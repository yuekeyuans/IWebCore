#include "IConfigurationTaskCatagory.h"

$PackageWebCoreBegin

QString IConfigurationTaskCatagory::name() const
{
    return "Configuration";
}

QStringList IConfigurationTaskCatagory::orders() const
{
    return {
        "Index 1"
    };
}

IOrderUnit::Priority IConfigurationTaskCatagory::family() const
{
    return Priority::High;
}

$PackageWebCoreEnd
