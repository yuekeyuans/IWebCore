#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IOrmTaskCatagory : public ITaskCatagoryInterface<IOrmTaskCatagory>
{
    Q_GADGET
    $AsCatagory(IOrmTaskCatagory)
private:
    IOrmTaskCatagory() = default;

public:
    virtual QString name() const final;
    virtual double order() const final;
};

$PackageWebCoreEnd
