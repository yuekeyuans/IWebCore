#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IEndupTaskCatagory : public ITaskCatagoryInterface<IEndupTaskCatagory>
{
    Q_DISABLE_COPY_MOVE(IEndupTaskCatagory)
    $AsCatagory(IEndupTaskCatagory)
public:
    IEndupTaskCatagory() = default;

public:
    virtual QString name() const final;
    virtual double order() const final;
};

$PackageWebCoreEnd
