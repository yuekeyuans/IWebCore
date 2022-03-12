#pragma once

#include "base/IHeaderUtil.h"
#include "orm/dialect/IOrmDialectWare.h"

$PackageWebCoreBegin

class IOrmEntityModelUnit
{
public:
    IOrmEntityModelUnit();
    virtual bool exec(const QString& sql) = 0;

    virtual QSqlDatabase& getDatabase() = 0;
    virtual IOrmDialectWare* getDialect() = 0;
};

$PackageWebCoreEnd
