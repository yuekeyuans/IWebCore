#pragma once

#include "core/test/ITestTaskUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled =true>
class ITestInterface : public ITestTaskUnit<T, enabled>, public QObject
{
public:
    ITestInterface() = default;
};

$PackageWebCoreEnd
