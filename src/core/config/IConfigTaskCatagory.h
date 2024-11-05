#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IConfigTaskCatagory : public ITaskCatagoryInterface<IConfigTaskCatagory>
{
public:
    virtual double $order() const final
    {
        return 0;
    }
};


$PackageWebCoreEnd
