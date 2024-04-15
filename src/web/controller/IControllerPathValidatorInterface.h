#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/unit/ITaskInstantUnit.h"

$PackageWebCoreBegin

// TODO: 这个地方拆分成两个 interface, 提供重载方法。
template<typename T, bool enabled = true>

class IControllerPathValidatorInterface : public ITaskInstantUnit<T, enabled>   // TODO: 这个也不对
{
public:
    using ValidatorFun = bool(*)(const QString&);

public:
    IControllerPathValidatorInterface() = default;
    virtual void task() = 0;

protected:
    void registerValidator(const QString& name, const QString& regexp);
    void registerValidator(const QString& name, ValidatorFun function);
};

namespace IControllerPathValidatorInterfaceHelper {
    using ValidateFun = bool(*)(const QString&);
    void registerValidator(const QString& name, const QString& regexp);
    void registerValidator(const QString& name, ValidateFun function);
}

template<typename T, bool enabled>
void IControllerPathValidatorInterface<T, enabled>::registerValidator(const QString& name, const QString& regexp){
    IControllerPathValidatorInterfaceHelper::registerValidator(name, regexp);
}

template<typename T, bool enabled>
void IControllerPathValidatorInterface<T, enabled>::registerValidator(const QString& name, const ValidatorFun fun){
    IControllerPathValidatorInterfaceHelper::registerValidator(name, fun);
}

$PackageWebCoreEnd
