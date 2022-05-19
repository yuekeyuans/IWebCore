#pragma once

#include "base/IHeaderUtil.h"
#include "core/assertion/IAssertJsonInterface.h"

$PackageWebCoreBegin

class ConfigurationAssertion : public IFatalAssertJsonInterface<ConfigurationAssertion>
{
    $UseInstance(ConfigurationAssertion)
public:
    ConfigurationAssertion() = default;
    virtual QString getAssertInfo() final;
};

$PackageWebCoreEnd
