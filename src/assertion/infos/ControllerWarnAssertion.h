#pragma once

#include "base/IHeaderUtil.h"
#include "assertion/IAssertJsonInterface.h"

$PackageWebCoreBegin

class ControllerWarnAssertion : public IWarnAssertJsonInterface<ControllerWarnAssertion>
{
    $UseInstance(ControllerWarnAssertion)
public:
    ControllerWarnAssertion() = default;
    virtual QString getAssertInfo() override;

};

$PackageWebCoreEnd
