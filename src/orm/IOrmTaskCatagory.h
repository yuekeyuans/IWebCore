#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IOrmTaskCatagory : public ITaskCatagoryInterface<IOrmTaskCatagory>
{
public:
    virtual double $order() const final
    {
        return 4;
    }
};

$PackageWebCoreEnd
