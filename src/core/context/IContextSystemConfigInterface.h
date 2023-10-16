#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/context/IContextTaskInterface.h"

$PackageWebCoreBegin

template<typename T, bool enabled>
class IContextSystemConfigInterface : public IContextTaskInterface<T, enabled>
{
public:
    IContextSystemConfigInterface() = default;
};

$PackageWebCoreEnd
