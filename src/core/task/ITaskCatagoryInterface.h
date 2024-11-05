#pragma once

#include "core/unit/ISingletonUnit.h"
#include "core/task/ITaskManage.h"
#include "core/task/ITaskCatagory.h"
#include "core/task/unit/ITaskCatagoryUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class ITaskCatagoryInterface : public ITaskCatagoryUnit<T, enabled>, public ISingletonUnit<T>
{
public:
    ITaskCatagoryInterface() = default;

public:
    virtual const char* $catagory() const final;

public:
    inline static const char* CATAGORY;
};

template<typename T, bool enabled>
const char* ITaskCatagoryInterface<T, enabled>::$catagory() const
{
    return CATAGORY;
}

template<typename T, bool enabled>
const char* ITaskCatagoryInterface<T, enabled>::CATAGORY = typeid(T).name();

$PackageWebCoreEnd
