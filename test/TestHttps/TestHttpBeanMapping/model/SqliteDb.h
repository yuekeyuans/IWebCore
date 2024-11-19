#pragma once

#include <IWebCore>

class SqliteDb : public IOrmDatabaseInterface<SqliteDb>
{
    Q_GADGET
    $AsDatabase(SqliteDb)
public:
    SqliteDb();

    virtual IOrmDataSource configDataSource() final;

    virtual void registerEntities() final;

};

