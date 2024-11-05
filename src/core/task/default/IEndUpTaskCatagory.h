#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IEndupTaskCatagory : public ITaskCatagoryInterface<IEndupTaskCatagory>
{
public:
    IEndupTaskCatagory() = default;

public:
    virtual double $order() const final;
};

$PackageWebCoreEnd
