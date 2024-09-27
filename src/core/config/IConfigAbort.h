#pragma once

#include "core/abort/IAbortInterface.h"

$PackageWebCoreBegin

class IConfigAbort : public IAbortInterface<IConfigAbort>
{
    $AsAbort(
        ConfigurationResolveJsonError
    )
protected:
    virtual QMap<int, QString> abortDescription() const final{
        return {
            {ConfigurationResolveJsonError, ""}
        };
    }
};

$PackageWebCoreEnd
