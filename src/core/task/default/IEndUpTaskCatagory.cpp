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

IOrderUnit::Family IEndupTaskCatagory::family() const
{
    return Family::System;
}

$PackageWebCoreEnd
