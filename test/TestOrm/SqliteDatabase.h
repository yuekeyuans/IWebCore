#pragma once

#include <IWebCore>

extern const char SqliteConnectionName[];

class SqliteDatabase : public IOrmDatabaseInterface<SqliteDatabase>
{
    $AsDatabase(SqliteDatabase)
public:
    SqliteDatabase();
    virtual IOrmDataSource configDataSource() final;
    virtual void registerTables() final;
};
