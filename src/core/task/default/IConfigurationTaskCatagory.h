#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IConfigurationTaskCatagory : public ITaskCatagoryInterface<IConfigurationTaskCatagory>
{
    Q_GADGET
    Q_DISABLE_COPY_MOVE(IConfigurationTaskCatagory)
    $AsCatagory(IConfigurationTaskCatagory)
private:
    IConfigurationTaskCatagory() = default;

public:
    virtual QString name() const final;
    virtual double order() const final;
};

$PackageWebCoreEnd
