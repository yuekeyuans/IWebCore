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
    virtual QStringList orders() const final;
    virtual Priority family() const final;
};

$PackageWebCoreEnd
