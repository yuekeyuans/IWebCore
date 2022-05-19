#pragma once

#include "core/assertion/IAssertInterface.h"
#include "core/assertion/IAssertPreProcessor.h"

$PackageWebCoreBegin

class ConfigurationMayNotInitializedAssert : public IWarningAssertInterface<ConfigurationMayNotInitializedAssert>
{
    $AsAssertion(ConfigurationMayNotInitializedAssert)
public:
    ConfigurationMayNotInitializedAssert() = default;

    virtual QString getKey() override;
    virtual QString getReason() override;
    virtual QString getDescription() override;
    virtual QString getSolution() override;
};

$PackageWebCoreEnd
