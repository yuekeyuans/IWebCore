#pragma once

#include "base/IHeaderUtil.h"
#include "assertion/IAssertJsonInterface.h"
$PackageWebCoreBegin

class OrmFatalAssertion : public IFatalAssertJsonInterface<OrmFatalAssertion>
{
    $UseInstance(OrmFatalAssertion)
public:
    OrmFatalAssertion() = default;

    virtual QString getAssertInfo() override;
};

$PackageWebCoreEnd
