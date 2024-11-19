#pragma once

#include <IWebCore>

extern const char SqliteConnectionName[];

class SqliteDatabase : public IOrmDatabaseInterface<SqliteDatabase>
{
    Q_GADGET
    $AsDatabase(SqliteDatabase)
public:
    SqliteDatabase();
    virtual IOrmDataSource configDataSource() final;
    virtual void registerEntities() final;
};
