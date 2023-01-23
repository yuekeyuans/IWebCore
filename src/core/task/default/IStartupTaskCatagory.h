#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IStartupTaskCatagory : public ITaskCatagoryInterface<IStartupTaskCatagory>
{
    Q_DISABLE_COPY_MOVE(IStartupTaskCatagory)
    $AsCatagory(IStartupTaskCatagory)
public:
    IStartupTaskCatagory() = default;

public:
    virtual QString name() const final;
    virtual double order() const final;
};

$PackageWebCoreEnd
