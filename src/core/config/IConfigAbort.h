#pragma once

#include "core/abort/IAbortInterface.h"

$PackageWebCoreBegin

class IConfigAbort : public IAbortInterface<IConfigAbort>
{
    $AsAbort(
        ConfigurationResolveJsonError,
        ConfigurationResolveTomlError
    )
protected:
    virtual QMap<int, QString> abortDescription() const final{
        return {
            {ConfigurationResolveJsonError, "error when parse json files"},
            {ConfigurationResolveTomlError, "error when parse toml files"}
        };
    }
};

$PackageWebCoreEnd
