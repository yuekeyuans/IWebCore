#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/IArgumentParserUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IArgumentParserInterface : public IArgumentParserUnit<T, enabled>
{
public:
    IArgumentParserInterface() = default;

    virtual void task(const QStringList& arguements) = 0;
};

$PackageWebCoreEnd
