#pragma once

#include "base/IHeaderUtil.h"
#include "assertion/IAssertInterface.h"

$PackageWebCoreBegin

class DeferRegisterNotAllowedFatal : public IFatalAssertInterface<DeferRegisterNotAllowedFatal>
{
    $UseInstance(DeferRegisterNotAllowedFatal)
public:
    DeferRegisterNotAllowedFatal() = default;

    virtual QString getKey() override;
    virtual QString getReason() override;
    virtual QString getDescription() override;
    virtual QString getSolution() override;
};

$PackageWebCoreEnd
