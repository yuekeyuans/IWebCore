#pragma once

#include "base/IHeaderUtil.h"
#include "orm/IOrmDatabaseInterface.h"
#include "orm/IOrmPreProcessor.h"

class SqliteDatabase : public IOrmDatabaseInterface
{
    $AsDatabase(SqliteDatabase)

public:
    SqliteDatabase();

public:
    virtual IOrmDataSource configDataSource() final;
    virtual void registerTables() final;
};

//$RegisterDatabase(SqliteDatabase)
