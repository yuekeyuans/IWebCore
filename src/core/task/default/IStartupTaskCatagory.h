#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IStartupTaskCatagory : public ITaskCatagoryInterface<IStartupTaskCatagory>
{
private:
    virtual const char* $catagory() const final;
    virtual double $order() const final;
};

$PackageWebCoreEnd


