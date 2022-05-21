#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/IArgumentTaskUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IArgumentTaskInterface : public IArgumentTaskUnit<T, enabled>
{
public:
    IArgumentTaskInterface() = default;

    virtual void task(const QStringList& arguements) = 0;
};

$PackageWebCoreEnd
