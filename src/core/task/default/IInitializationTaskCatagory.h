#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IInitializationTaskCatagory : public ITaskCatagoryInterface<IInitializationTaskCatagory>
{
    Q_DISABLE_COPY_MOVE(IInitializationTaskCatagory)
    $AsCatagory(IInitializationTaskCatagory)
private:
    IInitializationTaskCatagory() = default;

public:
    virtual QString name() const final;
    virtual double order() const final;
};

$PackageWebCoreEnd
