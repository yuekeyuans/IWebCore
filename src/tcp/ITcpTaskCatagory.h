#pragma once

#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class ITcpTaskCatagory : public ITaskCatagoryInterface<ITcpTaskCatagory>
{
public:
    virtual double $order() const final
    {
        return 49;
    }
};

$PackageWebCoreEnd
