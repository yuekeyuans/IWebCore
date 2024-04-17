#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class ITestTaskCatagory : public ITaskCatagoryInterface<ITestTaskCatagory>
{
public:
    virtual QString name() const final;
    virtual double order() const final;
    virtual bool isCatagoryDefaultEnabled() const;
};

$PackageWebCoreEnd
