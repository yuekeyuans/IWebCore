#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class ITestTaskCatagory : public ITaskCatagoryInterface<ITestTaskCatagory>
{
    $AsCatagory(ITestTaskCatagory)
private:
    ITestTaskCatagory() = default;

public:
    virtual QString name() const final;
    virtual double order() const final;
};

$PackageWebCoreEnd
