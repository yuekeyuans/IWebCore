#pragma once

#include <IWebCore>

class SqliteDb : public IOrmDatabaseInterface<SqliteDb>
{
    $AsDatabase(SqliteDb)
public:
    SqliteDb();

    virtual IOrmDataSource configDataSource() final;

    virtual void registerTables() final;

};

