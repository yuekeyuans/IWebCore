#pragma once

#include "base/IHeaderUtil.h"
#include "orm/model/IOrmEntityModeWare.h"
$PackageWebCoreBegin

template<typename T, const char * dbConnectionName = DefaultDatabaseName>
class IOrmViewModelInterface : public IOrmEntityModelWare<T, dbConnectionName>
{
    $UseWare
public:
    IOrmViewModelInterface() = default;

};

$PackageWebCoreEnd
