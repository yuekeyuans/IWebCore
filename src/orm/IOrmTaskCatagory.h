#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IOrmTaskCatagory : public ITaskCatagoryInterface<IOrmTaskCatagory>
{
public:
    virtual const char* $catagory() const final;
    virtual double $order() const final;
};

$PackageWebCoreEnd
