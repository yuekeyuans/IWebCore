﻿#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/unit/ITaskInstantUnit.h"

$PackageWebCoreBegin

namespace IControllerPathValidatorInterfaceProxy {
    using ValidateFun = bool(*)(const QString&);
    void registerValidator(const QString& name, const QString& regexp);
    void registerValidator(const QString& name, ValidateFun function);
}

template<typename T, bool enabled = true>
class IControllerPathValidatorInterface : public ITaskInstantUnit<T, enabled>
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

template<typename T, bool enabled>
void IControllerPathValidatorInterface<T, enabled>::registerValidator(const QString& name, const QString& regexp){
    IControllerPathValidatorInterfaceProxy::registerValidator(name, regexp);
}

template<typename T, bool enabled>
void IControllerPathValidatorInterface<T, enabled>::registerValidator(const QString& name, const ValidatorFun fun){
    IControllerPathValidatorInterfaceProxy::registerValidator(name, fun);
}

$PackageWebCoreEnd
