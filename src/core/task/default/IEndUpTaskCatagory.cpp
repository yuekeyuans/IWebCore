#include "IEndupTaskCatagory.h"

$PackageWebCoreBegin

QString IEndupTaskCatagory::name() const
{
    return "EndUp";
}

QStringList IEndupTaskCatagory::orders() const
{
    return {
        "Index -1"
    };
}

IOrderUnit::Priority IEndupTaskCatagory::family() const
{
    return Priority::Most;
}

$PackageWebCoreEnd
