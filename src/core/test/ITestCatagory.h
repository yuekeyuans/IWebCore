#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class ITestCatagory : public ITaskCatagoryInterface<ITestCatagory>
{
public:
    virtual QString name() const final;
    virtual double order() const final;
};

$PackageWebCoreEnd
