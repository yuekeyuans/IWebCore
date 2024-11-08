#pragma once

#include "core/util/IPackageUtil.h"

$PackageWebCoreBegin

namespace ISpawnUtil
{
    template<typename Ret, typename ... Args>
    Ret construct(Args... args);
}

$PackageWebCoreEnd
