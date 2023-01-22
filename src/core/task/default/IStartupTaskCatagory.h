#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IStartupTaskCatagory : public ITaskCatagoryInterface<IStartupTaskCatagory>
{
    $AsCatagory(IStartupTaskCatagory)
public:
    IStartupTaskCatagory() = default;

public:
    virtual QString name() const final;
    virtual QStringList orders() const final;
    virtual Priority family() const final;
};

$PackageWebCoreEnd
