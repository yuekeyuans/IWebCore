#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/unit/ISingletonUnit.h"
#include "http/IHttpTaskCatagory.h"
#include <functional>

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IHttpPathValidatorInterface : public ITaskWareUnit<T, IHttpTaskCatagory, enabled>, public ISingletonUnit<T>
{
public:
    using Validator = std::function<bool(const QString&)>;

public:
    virtual void $task() final;
    virtual double $order() const final;

public:
    virtual QString marker() const  = 0;
    virtual Validator validator() const  = 0;
};

class IHttpPathFunctorValidatorInterfaceHelper
{
    template<typename T, bool>
    friend class IHttpPathFunctorValidatorInterface;
private:
    static void registValidator(const QString& name, std::function<bool(const QString&)> validator);
};

template<typename T, bool enabled>
void IHttpPathValidatorInterface<T, enabled>::$task()
{
    IHttpPathFunctorValidatorInterfaceHelper::registValidator(this->marker(), this->validator());
}

template<typename T, bool enabled>
double IHttpPathValidatorInterface<T, enabled>::$order() const
{
    return 49;
}

$PackageWebCoreEnd
