#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/unit/ITaskInstantUnit.h"
#include "core/unit/ISingletonUnit.h"
#include <functional>

$PackageWebCoreBegin

struct IHttpPathFunctorValidatorWare
{
public:
    using Validator = std::function<bool(const QString&)>;

public:
    virtual QString name() = 0;
    virtual Validator validator()=0;
};

template<typename T, bool enabled=true>
class IHttpPathFunctorValidatorInterface : public IHttpPathFunctorValidatorWare,  public ITaskInstantUnit<T, enabled>, public ISingletonUnit<T>
{
public:
    IHttpPathFunctorValidatorInterface() = default;
    virtual void task() final;
};

namespace IHttpPathFunctorValidatorInterfaceHelper
{
    void registValidator(const QString& name, IHttpPathFunctorValidatorWare::Validator);
}

template<typename T, bool enabled>
void IHttpPathFunctorValidatorInterface<T, enabled>::task()
{
    IHttpPathFunctorValidatorInterfaceHelper::registValidator(name(), validator());
}


$PackageWebCoreEnd
