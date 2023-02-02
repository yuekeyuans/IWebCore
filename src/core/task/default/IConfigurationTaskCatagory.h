#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IConfigurationTaskCatagory : public ITaskCatagoryInterface<IConfigurationTaskCatagory>
{
    $AsCatagory(IConfigurationTaskCatagory)
private:
    IConfigurationTaskCatagory() = default;

public:
    virtual QString name() const final;
    virtual double order() const final;
};

$PackageWebCoreEnd
