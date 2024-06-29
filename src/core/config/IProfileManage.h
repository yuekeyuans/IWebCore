#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/config/IConfigManageInterface.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

class IProfileManage final : public IConfigManageInterface, public ISingletonUnit<IProfileManage>
{
public:
    IProfileManage() = default;

public:
    template<typename T>
    static T getBean(const QString& path, bool& ok);
};

template<typename T>
T IProfileManage::getBean(const QString& path, bool& ok)
{
    return static_cast<IConfigManageInterface*>(IProfileManage::instance())->getBean<T>(path, ok);
}

$PackageWebCoreEnd
