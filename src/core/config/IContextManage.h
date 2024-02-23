#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IConfigManageInterface.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

class IContextManage final : public IConfigManageInterface, public ISingletonUnit<IContextManage>
{
public:
    IContextManage() = default;

public:
    template<typename T>
    static T getBean(const QString& path, bool& ok);
};

template<typename T>
T IContextManage::getBean(const QString &path, bool& ok)
{
    return static_cast<IConfigManageInterface*>(IContextManage::instance())->getBean<T>(path, ok);
}

$PackageWebCoreEnd

#define IContextManageInstance IContextManage::instance()
