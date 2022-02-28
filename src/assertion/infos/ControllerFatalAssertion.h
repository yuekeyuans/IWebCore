#pragma once

#include "base/IHeaderUtil.h"
#include "assertion/IAssertJsonInterface.h"

$PackageWebCoreBegin

class ControllerFatalAssertion : public IFatalAssertJsonInterface<ControllerFatalAssertion>
{
    $UseInstance(ControllerFatalAssertion)
public:
    ControllerFatalAssertion() = default;
    virtual QString getAssertInfo() final;
};

$PackageWebCoreEnd
