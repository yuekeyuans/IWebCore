#pragma once

#include <IWebCore>

extern const char SqlLiteConnectionName[];

class SqliteDb : public IOrmDatabaseInterface<SqliteDb>
{
    $AsDatabase(SqliteDb)
public:
    SqliteDb();

public:
    virtual IOrmDataSource configDataSource() final;
    virtual void registerTables() final;
};

