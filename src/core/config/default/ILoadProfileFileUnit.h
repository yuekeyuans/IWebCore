#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class ILoadProfileFileUnit
{
public:
    ILoadProfileFileUnit() = default;

protected:
    virtual QStringList nameFilters() const = 0;

public:
    QStringList getFilteredPaths() const;

private:
    QStringList getConfigDirs() const;
    QStringList getConfigFiles() const;

};

$PackageWebCoreEnd
