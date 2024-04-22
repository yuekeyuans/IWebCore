#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/unit/ITaskInstantUnit.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

struct IHttpPathRegexpValidatorWare
{
public:
    using Validator = QString;

public:
    virtual QString name() = 0;
    virtual Validator validator();
};

template<typename T, bool enabled = true>
class IHttpPathRegexpValidatorInterface : public IHttpPathRegexpValidatorWare, public ITaskInstantUnit<T, enabled>, public ISingletonUnit<T>
{
public:
    IHttpPathRegexpValidatorInterface() = default;
    virtual void task() final;
};

namespace IHttpPathRegexpValidatorInterfaceHelper
{
    void registValidator(const QString& name, IHttpPathRegexpValidatorWare::Validator);
}

template<typename T, bool enabled>
void IHttpPathRegexpValidatorInterface<T, enabled>::task()
{
    IHttpPathRegexpValidatorInterfaceHelper::registValidator(name(), validator());
}

$PackageWebCoreEnd
