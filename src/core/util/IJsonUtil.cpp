#include "IJsonUtil.h"

$PackageWebCoreBegin
$IPackageBegin(IJsonUtil)

IJson toJson(bool value)
{
    return value;
}

IJson toJson(std::string&& value)
{
    return std::move(value);
}

IJson toJson(const std::string & value)
{
    return value;
}

IJson toJson(const QString& value)
{
    return value.toStdString();
}

IJson toJson(IJson && value)
{
    return std::move(value);
}

IJson toJson(const IJson & value)
{
    return value;
}

$IPackageEnd(IJsonUtil)
$PackageWebCoreEnd
