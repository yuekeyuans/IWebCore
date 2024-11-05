#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/unit/ITaskInstantUnit.h"
#include "core/unit/ISingletonUnit.h"
#include "http/IHttpControllerTaskCatagory.h"

$PackageWebCoreBegin

// TODO: check this

template<typename T, bool enabled = true>
class IHttpPathRegexpValidatorInterface : public IHttpPathRegexpValidatorWare, public ITaskInstantUnit<T, enabled>, public ISingletonUnit<T>
{
public:
    using Validator = QString;

public:
    IHttpPathRegexpValidatorInterface() = default;
    virtual void $task() final;
//    virtual QString $name() const final;
    virtual const char* $catagory() const final;
//    virtual double $order() const final;

public:
    virtual QString marker() const  = 0;
    virtual Validator validator() const  = 0;
};

class IHttpPathRegexpValidatorInterfaceHelper
{
    template<typename T, bool>
    friend class IHttpPathRegexpValidatorInterface;
private:
    void registValidator(const QString& name, const QString&);
};

template<typename T, bool enabled>
void IHttpPathRegexpValidatorInterface<T, enabled>::$task()
{
    IHttpPathFunctorValidatorInterfaceHelper::registValidator(this->marker(), this->validator());
}

//template<typename T, bool enabled>
//QString IHttpPathRegexpValidatorInterface<T, enabled>::$name() const
//{
//    return IMetaUtil::getTypename<T>();
//}

template<typename T, bool enabled>
const char* IHttpPathRegexpValidatorInterface<T, enabled>::$catagory() const
{
    return IHttpControllerTaskCatagory::CATAGORY;
}

//template<typename T, bool enabled>
//double IHttpPathRegexpValidatorInterface<T, enabled>::$order() const
//{
//    return 49;
//}


$PackageWebCoreEnd
