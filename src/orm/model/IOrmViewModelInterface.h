#pragma once

#include "base/IHeaderUtil.h"
#include "orm/model/IOrmEntityModeWare.h"
$PackageWebCoreBegin

template<typename T, const char * dbConnectionName = DefaultDatabaseName>
class IOrmViewModelInterface
{
public:
    IOrmViewModelInterface() = default;

private:
    virtual void pureVirtual() = 0;
};

$PackageWebCoreEnd
