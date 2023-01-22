#include "IStartupTaskCatagory.h"

$PackageWebCoreBegin

QString IStartupTaskCatagory::name() const
{
    return "StartUp";
}

QStringList IStartupTaskCatagory::orders() const
{
    return {
        "Index 0"
    };
}

IOrderUnit::Family IStartupTaskCatagory::family() const
{
    return Family::System;
}

$PackageWebCoreEnd
