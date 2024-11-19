#pragma once

#include "core/util/IMetaUtil.h"
#include "json.hpp"
#include "core/util/IPackageUtil.h"
#include <iostream>
#include <fstream>

$PackageWebCoreBegin

using IJson = nlohmann::json;
Q_DECLARE_METATYPE(IJson)

$PackageWebCoreEnd
