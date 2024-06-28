#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/abort/IAbortInterface.h"

$PackageWebCoreBegin

class IGlobalAbort : public IAbortInterface<IGlobalAbort>
{
    $AsAbort(
        UnVisibleMethod,
        UnReachableCode,
        UnImplimentedMethod,
        SingletonInstanceCreateError
    )
public:
    IGlobalAbort() = default;

protected:
    virtual QMap<int, QString> abortDescription() const final;
    virtual QString abortComment() final;
};

$PackageWebCoreEnd
