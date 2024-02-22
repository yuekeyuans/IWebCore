#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IEndupTaskCatagory : public ITaskCatagoryInterface<IEndupTaskCatagory>
{
public:
    virtual QString name() const final;
    virtual double order() const final;
};

$PackageWebCoreEnd
