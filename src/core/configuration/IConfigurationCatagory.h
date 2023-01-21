#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IConfigurationCatagory : public ITaskCatagoryInterface<IConfigurationCatagory>
{
    $UseInstance(IConfigurationCatagory)
public:
    IConfigurationCatagory();

public:
    virtual QString getName() final;
};

$PackageWebCoreEnd
