#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class ILoadProfileFileUnit
{
public:
    ILoadProfileFileUnit() = default;

protected:
    virtual QStringList nameFilters() const = 0;

public:
    QStringList getValidatedPaths() const;

private:
    QStringList getConfigDirs() const;
    QStringList getConfigFiles() const;

};

$PackageWebCoreEnd
