#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/assert/IAbortInterface.h"

$PackageWebCoreBegin

class IGlobalAbort : public IAbortInterface<IGlobalAbort>
{
    $AsAbort(
        UnVisibleMethod
    )
public:
    IGlobalAbort() = default;

protected:
    virtual QMap<int, QString> abortDescription() const final;
    virtual QString abortComment() final;
};

$PackageWebCoreEnd
