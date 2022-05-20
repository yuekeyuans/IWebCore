#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/IConfigurationTaskUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IConfigurationTaskInterface : public IConfigurationTaskUnit<T, enabled>
{
public:
    IConfigurationTaskInterface() = default;

    virtual void task() =0;
};

$PackageWebCoreEnd
