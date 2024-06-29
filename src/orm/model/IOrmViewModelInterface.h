﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "orm/model/IOrmEntityModeWare.h"
$PackageWebCoreBegin

template<typename T, const char * dbConnectionName = DefaultDatabaseName>
class IOrmViewModelInterface : public IOrmEntityModelWare<T, dbConnectionName>
{
public:
    using IOrmEntityModelWare<T, dbConnectionName>::exec;
    using IOrmEntityModelWare<T, dbConnectionName>::getDialect;
    using IOrmEntityModelWare<T, dbConnectionName>::getDatabase;

public:
    IOrmViewModelInterface() = default;

};

$PackageWebCoreEnd
