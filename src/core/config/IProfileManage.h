#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IConfigManageInterface.h"

$PackageWebCoreBegin

class IProfileManage final : public IConfigManageInterface
{
    $UseInstance(IProfileManage)
private:
    IProfileManage() = default;

public:
    template<typename T>
    static T getBean(const QString& path, bool* ok=nullptr);
};

template<typename T>
T IProfileManage::getBean(const QString& path, bool* ok)
{
    return static_cast<IConfigManageInterface*>(IProfileManage::instance())->getBean<T>(path, ok);
}

$PackageWebCoreEnd
