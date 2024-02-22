#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IControllerTaskCatagory : public ITaskCatagoryInterface<IControllerTaskCatagory>
{
public:
    virtual QString name() const final;
};

$PackageWebCoreEnd
