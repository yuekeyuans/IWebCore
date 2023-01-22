#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IEndupTaskCatagory : public ITaskCatagoryInterface<IEndupTaskCatagory>
{
    $AsCatagory(IEndupTaskCatagory)
public:
    IEndupTaskCatagory() = default;

public:
    virtual QString name() const final;
    virtual QStringList orders() const final;
    virtual Priority family() const final;

};

$PackageWebCoreEnd
