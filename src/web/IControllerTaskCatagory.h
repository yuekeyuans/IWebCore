#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IControllerTaskCatagory : public ITaskCatagoryInterface<IControllerTaskCatagory>
{
    Q_GADGET
    $AsCatagory(IControllerTaskCatagory)
public:
    IControllerTaskCatagory() = default;

public:
    virtual QString name() const final;
};

$PackageWebCoreEnd
