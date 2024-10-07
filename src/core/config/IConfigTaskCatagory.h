#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IConfigTaskCatagory : public ITaskCatagoryInterface<IConfigTaskCatagory>
{
public:
    IConfigTaskCatagory() = default;

public:
    virtual const char* $catagory() const final;
    virtual double $order() const final;
};

$PackageWebCoreEnd
