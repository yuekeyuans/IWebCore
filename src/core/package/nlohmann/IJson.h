#pragma once

#include "core/util/IPackageUtil.h"
#include <json.hpp>

$PackageWebCoreBegin

using IJson = nlohmann::json;
Q_DECLARE_METATYPE(IJson)

Q_DECLARE_METATYPE(std::string)

$PackageWebCoreEnd
