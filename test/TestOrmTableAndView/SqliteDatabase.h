#pragma once

#include <IWebCore>

class SqliteDatabase : public IOrmDatabaseInterface<SqliteDatabase>
{
    $AsDatabase(SqliteDatabase)
public:
    SqliteDatabase();

    virtual IOrmDataSource configDataSource() override;

    virtual void registerTables() override;
};

