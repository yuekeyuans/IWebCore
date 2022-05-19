#include "ConfigurationMayNotInitializedAssert.h"

$PackageWebCoreBegin

QString ConfigurationMayNotInitializedAssert::getKey()
{
    return "configuration_may_not_initialized";
}

QString ConfigurationMayNotInitializedAssert::getReason()
{
    return "the configuration will complete at the begin of main. "
           "when you use configuration when configuration not complete, "
           "this warning popup.";
}

QString ConfigurationMayNotInitializedAssert::getDescription()
{
    return "";
}

QString ConfigurationMayNotInitializedAssert::getSolution()
{
    return "change your code, or ignore this warning";
}

$PackageWebCoreEnd
