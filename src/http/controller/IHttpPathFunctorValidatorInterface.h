#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/unit/ISingletonUnit.h"
#include <functional>

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IHttpPathFunctorValidatorInterface : public ITaskWareUnit<T, enabled>, public ISingletonUnit<T>
{
public:
    using Validator = std::function<bool(const QString&)>;

public:
    IHttpPathFunctorValidatorInterface() = default;
    virtual void $task() final;
    virtual QString $name() const final;
    virtual const char* $catagory() const final;
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
void IHttpPathFunctorValidatorInterface<T, enabled>::$task()
{
    IHttpPathFunctorValidatorInterfaceHelper::registValidator(this->marker(), this->validator());
}

template<typename T, bool enabled>
QString IHttpPathFunctorValidatorInterface<T, enabled>::$name() const
{
    return IMetaUtil::getTypename<T>();
}

template<typename T, bool enabled>
const char* IHttpPathFunctorValidatorInterface<T, enabled>::$catagory() const
{
    return "HttpController";
}

template<typename T, bool enabled>
double IHttpPathFunctorValidatorInterface<T, enabled>::$order() const
{
    return 49;
}

$PackageWebCoreEnd
