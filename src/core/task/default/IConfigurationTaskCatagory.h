#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IConfigurationTaskCatagory : public ITaskCatagoryInterface<IConfigurationTaskCatagory>
{
    Q_GADGET
    $AsCatagory(IConfigurationTaskCatagory)
public:
    IConfigurationTaskCatagory() = default;

public:
    virtual QString name() const final;
    virtual double order() const final;
};

$PackageWebCoreEnd
