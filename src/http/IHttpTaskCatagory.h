#pragma once

#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IHttpTaskCatagory : public ITaskCatagoryInterface<IHttpTaskCatagory>
{
public:
    virtual double $order() const final
    {
        return 100;
    }
};

$PackageWebCoreEnd
