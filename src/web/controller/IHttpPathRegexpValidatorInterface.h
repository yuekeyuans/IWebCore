#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/unit/ITaskInstantUnit.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

// TODO: 这个地方拆分成两个 interface, 提供重载方法。
template<typename T, bool enabled = true>
class IHttpPathRegexpValidatorInterface : public ITaskInstantUnit<T, enabled>, public ISingletonUnit<T>
{
public:
    using ValidatorFun = bool(*)(const QString&);

public:
    IHttpPathRegexpValidatorInterface() = default;
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
void IHttpPathRegexpValidatorInterface<T, enabled>::registerValidator(const QString& name, const QString& regexp){
    IControllerPathValidatorInterfaceHelper::registerValidator(name, regexp);
}

template<typename T, bool enabled>
void IHttpPathRegexpValidatorInterface<T, enabled>::registerValidator(const QString& name, const ValidatorFun fun){
    IControllerPathValidatorInterfaceHelper::registerValidator(name, fun);
}

$PackageWebCoreEnd
