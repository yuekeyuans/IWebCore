#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/IConfigUnit.h"

$PackageWebCoreBegin

class IProfileManage : public IConfigUnit
{
    $UseInstance(IProfileManage)
private:
    IProfileManage() = default;

public:
    template<typename T>
    T getBean(const QString& path, bool* ok=nullptr);
};

template<typename T>
T IProfileManage::getBean(const QString& path, bool* ok)
{
    return {};
}

$PackageWebCoreEnd
