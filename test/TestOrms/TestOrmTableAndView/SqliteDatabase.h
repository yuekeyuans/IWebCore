#pragma once

#include <IWebCore>

class SqliteDatabase : public IOrmDatabaseInterface<SqliteDatabase>
{
    Q_GADGET
    $AsDatabase(SqliteDatabase)
public:
    SqliteDatabase();

    virtual IOrmDataSource configDataSource() override;

    virtual void registerEntities() override;
};

