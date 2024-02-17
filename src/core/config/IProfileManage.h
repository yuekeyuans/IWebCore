#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/IConfigUnit.h"

$PackageWebCoreBegin

class IProfileManage final : public IConfigUnit
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
    auto value = IProfileManage::instance()->getConfig(path, ok);
    if(*ok){
        return T::fromJson(value.toObject());
    }
    return {};
}

$PackageWebCoreEnd
