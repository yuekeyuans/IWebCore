#pragma once

#include "assertion/IAssertJsonInterface.h"
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class OrmWarnAssertion : public IWarnAssertJsonInterface<OrmWarnAssertion>
{
    $UseInstance(OrmWarnAssertion)
public:
    OrmWarnAssertion() = default;

    virtual QString getAssertInfo() final;
};

$PackageWebCoreEnd
